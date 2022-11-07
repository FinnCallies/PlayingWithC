#include <string.h>
#include "crypt_util.h"
#include "vigenere.h"


void enc_vigenere(byte *plain, int len, byte *key, int key_len, byte *cipher)
{
    for (int i = 0; i < len; i++)
        cipher[i] = (plain[i] + key[i % key_len]) % 256;
}

void dec_vigenere(byte *cipher, int len, byte *key, int key_len, byte *plain)
{
    for (int i = 0; i < len; i++)
        plain[i] = (cipher[i] - key[i % key_len]) % 256;
}

void enc_vigenere_ecb(byte *plain, int len, byte *key, byte *cipher, int block_size)
{
    for (int i = 0; i < len/block_size; i ++) {
        enc_vigenere(plain + i * block_size, block_size, key, block_size, cipher + i * block_size);
    }

    printf("ENCRYPTED PLAINTEXT: ");
    print_bytes_by_block(cipher, len, block_size);
    printf("\n");
    printf("\n");
}

void dec_vigenere_ecb(byte *cipher, int len, byte *key, byte *plain, int block_size)
{
    for (int i = 0; i < len/block_size; i ++) {
        dec_vigenere(cipher + i * block_size, block_size, key, block_size, plain + i * block_size);
    }

    printf("DECRYPTED CIPHERTEXT: ");
    print_bytes_by_block(plain, len, block_size);
    printf("\n");
    printf("\n");
}

void enc_vigenere_cbc(byte *plain, int len, byte *key, byte *cipher, byte *iv, int block_size, bool logs)
{
    byte *xor_block = (byte *)calloc(block_size, sizeof(byte));
    byte *xor = (byte *)calloc(block_size, sizeof(byte));

    if (logs)
    {
        printf("iv: ");
        print_bytes(iv, block_size);
        printf("\n");
    }

    // for every block in plain...
    memcpy(xor, iv, block_size);
    for (int i = 0; i < len/block_size; i++) {
        byte *plain_block = plain + i * block_size;

        if (logs) {
        printf("plain_block: ");
        print_bytes(plain_block, block_size);
        }

        // xor xor_block with xor
        for (int j = 0; j < block_size; j++) {
            xor_block[j] = plain_block[j] ^ xor[j];
            if (logs) {
                printf("plain_block[%d] = %02x; xor[%d] = %02x; ", j, plain_block[j], j, xor[j]);
                printf("xor_block[%d] = %02x\n", j, xor_block[j]);
            }
        }
        if (logs) {
            printf("xor_block: ");
            print_bytes(xor_block, block_size);
        }

        // block cipher encrypt
        enc_vigenere(xor_block, block_size, key, block_size, cipher + i * block_size);
        if (logs) {
            printf("encrypted xor_block: ");
            print_bytes(cipher + i * block_size, block_size);
        }

        // update xor
        memcpy(xor, cipher + i * block_size, block_size);

        if (logs) printf("\n");
    }

    printf("ENCRYPTED PLAINTEXT: ");
    print_bytes_by_block(cipher, len, block_size);
    printf("\n");
    printf("\n");

    free(xor_block);
    free(xor);
}

void dec_vigenere_cbc(byte *cipher, int len, byte *key, byte *plain, byte *iv, int block_size, bool logs)
{
    byte *xor_block = (byte *)calloc(block_size, sizeof(byte));
    byte *xor = (byte *)calloc(block_size, sizeof(byte));
    
    if (logs) {
        printf("xor: ");
        print_bytes(xor, block_size);
        printf("\n");
    }

    // for every block in plain...
    for (int i = (len/block_size) - 1; i >= 0; i--) {
        byte *cipher_block = cipher + i * block_size;

        // set xor for this round
        if (i != 0) {
            memcpy(xor, cipher + (i - 1) * block_size, block_size);
            if (logs) {
                printf("xor: ");
                print_bytes(xor, block_size);
            }
        } else {
            memcpy(xor, iv, block_size);
        }

        if (logs) {
            printf("cipher_block: ");
            print_bytes(cipher_block, block_size);
        }

        // block cipher decrypt
        dec_vigenere(cipher_block, block_size, key, block_size, xor_block);
        if (logs) {
            printf("decrypted cipher_block(xor_block): ");
            print_bytes(xor_block, block_size);
        }

        // xor xor_block with xor
        for (int j = 0; j < block_size; j++) {
            plain[i * block_size + j] = xor_block[j] ^ xor[j];
            if (logs) {
                printf("xor_block[%d] = %02x; xor[%d] = %02x; ", j, xor_block[j], j, iv[j]);
                printf("plain_block[%d] = %02x\n", j, plain[i * block_size + j]);
            }
        }
        if (logs) {
            print_bytes(plain + i * block_size, block_size);
            printf("\n");
        }
    }

    printf("DECRYPTED CIPHERTEXT: ");
    print_bytes_by_block(plain, len, block_size);
    printf("\n");
    printf("\n");

    free(xor_block);
    free(xor);
}

void enc_vigenere_ctr(byte *plain, int len, byte *key, byte *cipher, byte *nonce, int block_size)
{
    byte *counter = (byte *)calloc(block_size, sizeof(byte));
    byte *nonce_xor_counter = (byte *)calloc(block_size, sizeof(byte));
    byte *encrypted = (byte *)calloc(block_size, sizeof(byte));

    for (int i = 0; i < len / block_size; i++) {
        xor_bytes(nonce_xor_counter, nonce, counter, block_size);

        enc_vigenere(nonce_xor_counter, block_size, key, block_size, encrypted);

        xor_bytes(cipher + i * block_size, plain + i * block_size, encrypted, block_size);
        
        inc_counter(counter, block_size);
    }

    printf("ENCRYPTED PLAINTEXT: ");
    print_bytes_by_block(cipher, len, block_size);
    printf("\n");
    printf("\n");

    free(counter);
    free(nonce_xor_counter);
    free(encrypted);
}

void dec_vigenere_ctr(byte *cipher, int len, byte *key, byte *plain, byte *nonce, int block_size)
{
    byte *counter = (byte *)calloc(block_size, sizeof(byte));
    byte *nonce_xor_counter = (byte *)calloc(block_size, sizeof(byte));
    byte *decrypted = (byte *)calloc(block_size, sizeof(byte));

    for (int i = 0; i < len / block_size; i++) {
        xor_bytes(nonce_xor_counter, nonce, counter, block_size);

        enc_vigenere(nonce_xor_counter, block_size, key, block_size, decrypted);

        xor_bytes(plain + i * block_size, cipher + i * block_size, decrypted, block_size);
        
        inc_counter(counter, block_size);
    }

    printf("DECRYPTED CIPHERTEXT: ");
    print_bytes_by_block(plain, len, block_size);
    printf("\n");
    printf("\n");

    free(counter);
    free(nonce_xor_counter);
    free(decrypted);
}
