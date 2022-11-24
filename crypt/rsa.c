#include "crypt_util.h"
#include "rsa.h"
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


void print_key_pair(rsa_key_pair key_pair) 
{
    printf("prv_key: %d, pub_key: %d, n: %d\n", key_pair.prv_key.d, key_pair.pub_key.e, key_pair.pub_key.n);
}

void eeA(int a, int b, int *x, int *y)
{
    int x1, y1;
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return;
    }
    eeA(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
}

bool isPrime(int n) 
{
    if (n < 2) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int gen_prime(int size)
{
    srand(time(NULL));
    int r = rand() % size;
    while (!isPrime(r)) {
        r = rand() % size;
    }
    return r;
}

rsa_key_pair rsa_gen_key_pair(int size)
{
    rsa_key_pair key_pair;
    int e = pow(2, size) + 1;
    int p = gen_prime(pow(2, size));
    int q = gen_prime(pow(2, size));
    while (p == q) q = gen_prime(pow(2, size));
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int d = 0;
    int y = 0;
    eeA(e, phi, &d, &y);
    if (d < 0) d += phi;
    key_pair.pub_key.e = e;
    key_pair.pub_key.n = n;
    key_pair.prv_key.d = d;
    key_pair.prv_key.n = n;


    // printf("e = %d, p = %d, q = %d, n = %d, phi = %d, d = %d, y = %d\n", e, p, q, n, phi, d, y);
    return key_pair;
}

rsa_key_pair rsa_gen_key_pair_p_q(int size, int p, int q)
{
    rsa_key_pair key_pair;
    int e = pow(2, size) + 1;
    while (p == q) q = gen_prime(pow(2, size));
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int d = 0;
    int y = 0;
    eeA(e, phi, &d, &y);
    if (d < 0) d += phi;
    key_pair.pub_key.e = e;
    key_pair.pub_key.n = n;
    key_pair.prv_key.d = d;
    key_pair.prv_key.n = n;


    printf("e = %d, p = %d, q = %d, n = %d, phi = %d, d = %d, y = %d\n", e, p, q, n, phi, d, y);
    return key_pair;
}

/*  ---------- KNOWN KEY PAIRS ----------
    1. e = 17, p = 11, q = 13, n = 143, phi = 120, d = 113, y = 1
    2. e = 23, n = 143, d = 47
*/
rsa_key_pair rsa_known_key_pair(int i)
{
    rsa_key_pair key_pair;

    switch (i) {
        case 1:
            key_pair.pub_key.e = 23;
            key_pair.pub_key.n = 143;
            key_pair.prv_key.d = 47;
            key_pair.prv_key.n = 143;
            break;
        case 2:
            key_pair.pub_key.e = 17;
            key_pair.pub_key.n = 143;
            key_pair.prv_key.d = 113;
            key_pair.prv_key.n = 143;
            break;
        default:
            break;
    }
    return key_pair;
}

int expo_mod(int num, int expo, int mod)
{
    if (expo == 0) return 1;
    int ret = 1;
    for (int i = 0; i < expo; i++)
    {
        ret = (ret * num) % mod;
    }
    return ret;
}  

void enc_rsa(int *plain, int len, int *cipher, rsa_pub_key key)
{
    for (int i = 0; i < len; i++)
    {
        cipher[i] = expo_mod(plain[i], key.e, key.n);
        // printf("%d->%d ", msg[i], enc);
    }
    // printf("\n");
}

void dec_rsa(int *cipher, int len, int *plain, rsa_prv_key key)
{
    for (int i = 0; i < len; i++)
    {
        plain[i] = expo_mod(cipher[i], key.d, key.n);
        // printf("%d->%d ", array[i], array2[i]);
    }
    // printf("\n");
}

void rsa_demo()
{
    int byte_cnt = 16;

    int *rsa_plain = (int *)calloc(byte_cnt, sizeof(int));
    int *rsa_encoded = (int *)calloc(byte_cnt, sizeof(int));
    int *rsa_decoded = (int *)calloc(byte_cnt, sizeof(int));

    // GENERATE RSA KEY PAIR
    rsa_key_pair key_pair;
    key_pair = rsa_known_key_pair(2);
    print_key_pair(key_pair);
    printf("\n");

    // GENERATE PLAINTEXT
    generate_rndm_ints(rsa_plain, byte_cnt, key_pair.pub_key.n);
    printf("PLAIN : ");
    for (int i = 0; i < byte_cnt; i++) {
        printf("%d ", rsa_plain[i]);
    }
    printf("\n");

    // ENCRYPT PLAINTEXT
    enc_rsa(rsa_plain, byte_cnt, rsa_encoded, key_pair.pub_key);
    printf("CIPHER: ");
    // print_bytes(encrypted, byte_cnt);
    for (int i = 0; i < byte_cnt; i++) {
        printf("%d ", rsa_encoded[i]);
    }
    printf("\n");

    // DECRYPT CIPHERTEXT
    dec_rsa(rsa_encoded, byte_cnt, rsa_decoded, key_pair.prv_key);
    printf("PLAIN : ");
    for (int i = 0; i < byte_cnt; i++) {
        printf("%d ", rsa_decoded[i]);
    }
    printf("\n");


    // free some shit
    free(rsa_plain);
    free(rsa_encoded);
    free(rsa_decoded);
}
