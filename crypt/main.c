#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "crypt_util.h"
#include "caesar.h"
#include "vigenere.h"
#include "rsa.h"

/* void enc_dec()
{
    bool logs = false;
    int block_size = 16;
    int text_size = 256;


    byte *key = (byte *)calloc(block_size, sizeof(byte));
    byte *plaintext = (byte *)calloc(text_size, sizeof(byte));
    byte *encrypted = (byte *)calloc(text_size, sizeof(byte));
    byte *decrypted = (byte *)calloc(text_size, sizeof(byte));
    byte *iv = (byte *)calloc(block_size, sizeof(byte));

    gen_rndm_block(key, block_size);
    gen_rndm_block(iv, block_size);
    gen_rndm_block(plaintext, text_size);


    printf("KEY: ");
    print_bytes(key, block_size);
    printf("IV: ");
    print_bytes(iv, block_size);
    printf("PLAINTEXT: ");
    print_bytes_by_block(plaintext, text_size, block_size);
    printf("\n");
    printf("\n");


    // enc_vigenere_ecb(plaintext, text_size, key, encrypted, block_size);
    // dec_vigenere_ecb(encrypted, text_size, key, decrypted, block_size);

    // enc_vigenere_cbc(plaintext, text_size, key, encrypted, iv, block_size, logs);
    // dec_vigenere_cbc(encrypted, text_size, key, decrypted, iv, block_size, logs);

    int prv_key;
    int pub_key;
    int n;

    gen_rsa_key_pair(11, 13, &prv_key, &pub_key, &n);
    printf("prv_key: %d, pub_key: %d, n: %d\n", prv_key, pub_key, n);

    enc_rsa(plaintext, text_size, pub_key, n, encrypted);
    dec_rsa(encrypted, text_size, prv_key, n, decrypted);


    if (is_equal(plaintext, decrypted, text_size)) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
    

    free(key);
    free(plaintext);
    free(encrypted);
    free(decrypted);
    free(iv);
} */

int main(int argc, char const *argv[])
{

    // enc_dec();
    
    
    generate_rsa_key_pair();
    

    return 0;
}
