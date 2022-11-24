#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
// #include <math.h>
#include "crypt_util.h"
#include "caesar.h"
#include "vigenere.h"
#include "rsa.h"
#include "rc4.h"
#include "base64.h"


int main(int argc, char const *argv[])
{
    // vigenere_demo();
    rsa_demo();
    // b64_demo();

    /* rsa_pub_key key;
    key.n = 65536;
    long array[20];
    long array2[20];
    for (int i = 0; i < 20; i++)
    {
        array[i] = 0;
        array2[i] = 0;
    }
    

    byte *bytes = (byte *)calloc(60, sizeof(byte));
    generate_rndm_plaintext(bytes, 40);
    print_bytes(bytes, 40);
    bytes2longs(bytes, array, 20, key);
    for (int i = 0; i < 40; i++)
    {
        bytes[i] = 0;
    }
    

    for (int i = 0; i < 20; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    longs2bytes(array, bytes, 20, key);
    print_bytes(bytes, 40);
    
    bytes2longs(bytes, array2, 20, key);
    for (int i = 0; i < 20; i++) {
        printf("%d ", array2[i]);
    }
    printf("\n");

    free(bytes); */

    return 0;
}
