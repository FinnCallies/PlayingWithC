#include <stdbool.h>
#include "crypt_util.h"


void construct_key_from_sbox(byte *sbox, int block_size, byte *key)
{
    for (int i = 0; i < block_size; i++) {
        key[i] = (1 + (block_size - sbox[i])) % block_size;
    }
    key[0] -= 1;
}

void ksa(byte *key, int key_len, byte *sbox, int block_size, bool construct_key)
{
    int j = 0;

    for (int i = 0; i < block_size; i++) {
        sbox[i] = i;
    }

    if (construct_key) {
        construct_key_from_sbox(sbox, block_size, key);
    }

    for (int  i = 0; i < block_size; i++)
    {
        byte temp;
        j = (j + sbox[i] + key[i % key_len]) % block_size;
        temp = sbox[i];
        sbox[i] = sbox[j];
        sbox[j] = temp;
    }
    j = 0;
}

void generate_keystream(byte *key, int key_len, int block_size, byte *keystream)
{
    int i = 0;
    int j = 0;
    byte temp;
    byte *sbox = (byte *)calloc(block_size, sizeof(byte));

    ksa(key, block_size, sbox, block_size, false);

    for (int k = 0; k < block_size; k++)
    {
        i = (i + 1) % block_size;
        j = (j + sbox[i]) % block_size;
        temp = sbox[i];
        sbox[i] = sbox[j];
        sbox[j] = temp;
        keystream[k] = sbox[(sbox[i] + sbox[j]) % block_size];
    }
}

void enc_rc4(byte *plaintext, int len, byte *keystream, int block_size, byte *ciphertext)
{
    for (int i = 0; i < len; i++)
    {
        ciphertext[i] = plaintext[i] ^ keystream[i % block_size];
    }
}

void dec_rc4(byte *ciphertext, int len, byte *keystream, int block_size, byte *plaintext)
{
    for (int i = 0; i < len; i++)
    {
        plaintext[i] = ciphertext[i] ^ keystream[i % block_size];
    }
}
