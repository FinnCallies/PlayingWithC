#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "crypt_util.h"
#include "caesar.h"
#include "vigenere.h"


int main(int argc, char const *argv[])
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


    // enc_vignere_ecb(plaintext, text_size, key, encrypted, block_size);
    // dec_vignere_ecb(encrypted, text_size, key, decrypted, block_size);

    enc_vignere_cbc(plaintext, text_size, key, encrypted, iv, block_size, logs);
    dec_vignere_cbc(encrypted, text_size, key, decrypted, iv, block_size, logs);



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

    return 0;
}
