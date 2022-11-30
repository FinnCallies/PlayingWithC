#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "crypt_util.h"
#include "caesar.h"
#include "vigenere.h"
#include "rsa.h"
#include "rc4.h"
#include "base64.h"


int main(int argc, char const *argv[])
{
    // vigenere_demo();
    // rsa_demo();
    // b64_demo();

    long byte_cnt = 16;

    char *plaintext = "Never gonna give you up, never gonna let you down, never gonna run around and desert you, never gonna make you cry, never gonna say goodbye, never gonna tell a lie and hurt you";
    int len = strlen(plaintext);
    byte *bytes = (byte *)calloc(len, sizeof(byte));
    memcpy(bytes, plaintext, len);
    printf("Plaintext: %s\n", bytes);
    print_bytes(bytes, len);

    rsa_key_pair key_pair = rsa_gen_key_pair(16);
    print_key_pair(key_pair);
    printf("\n");

    long *rsa_plain = (long *)calloc(len, sizeof(long));
    long *rsa_encoded = (long *)calloc(len, sizeof(long));
    long *rsa_decoded = (long *)calloc(len, sizeof(long));
    // byte *bytes = (byte *)calloc(len, sizeof(byte));

    os2ip(bytes, rsa_plain, len);

    // ENCRYPT PLAINTEXT
    enc_rsa(rsa_plain, len, rsa_encoded, key_pair.pub_key);
    i2osp(rsa_encoded, bytes, len);
    printf("CIPHER: ");
    print_bytes(bytes, len);
    /* for (long i = 0; i < len; i++) {
        printf("%d ", rsa_encoded[i]);
    }
    printf("\n"); */
    printf("\n");

    // DECRYPT CIPHERTEXT
    dec_rsa(rsa_encoded, len, rsa_decoded, key_pair.prv_key);
    i2osp(rsa_decoded, bytes, len);
    printf("PLAIN : ");
    i2osp(rsa_decoded, bytes, len);
    print_bytes(bytes, len);
    printf("Plaintext: %s\n", bytes);
    /* for (long i = 0; i < len; i++) {
        printf("%d ", rsa_decoded[i]);
    }
    printf("\n"); */
    printf("\n");


    // free some shit
    free(rsa_plain);
    free(rsa_encoded);
    free(rsa_decoded);
    free(bytes);

    return 0;
}
