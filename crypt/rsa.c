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

void longs2bytes(long *array, byte *bytes, long len, rsa_pub_key pub_key) 
{
    long n = pub_key.n - 1;
    long bytes_per_long = (long) (log2(n) / 8) + 1;

    for (int i = 0; i < len * bytes_per_long; i++) {
        bytes[i] = 0;
    }
    

    for (long i = 0; i < len; i++) {
        long value = array[i];
        for (long j = 0; j < bytes_per_long; j++)
        {
            if (j == bytes_per_long - 1) {
                bytes[i * bytes_per_long + j] = value % 256;
            } else {
                bytes[i * bytes_per_long + j] = value / pow(2, 8 * (bytes_per_long - j - 1));
                value = value % (long) pow(2, 8 * (bytes_per_long - j - 1));
            }
        }
    }
}

void bytes2longs(byte *bytes, long *array, long len, rsa_pub_key pub_key)
{
    long n = pub_key.n - 1;
    long bytes_per_long = (long) (log2(n) / 8) + 1;

    for (int i = 0; i < len; i++) {
        array[i] = 0;
    }
    

    for (long i = 0; i < len; i++)
    {
        for (long j = 0; j < bytes_per_long; j++)
        {
            if (j == bytes_per_long - 1) {
                array[i] += bytes[i * bytes_per_long + j];
            } else {
                array[i] += bytes[i * bytes_per_long + j] * pow(2, 8 * (bytes_per_long - j - 1));
            }
        }
    }
}

void eeA(long a, long b, long *x, long *y)
{
    long x1, y1;
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

bool isPrime(long n) 
{
    if (n < 2) return false;
    for (long i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

long gen_prime(long size)
{
    srand(time(NULL));
    long r = rand() % size;
    while (!isPrime(r)) {
        r = rand() % size;
    }
    return r;
}

rsa_key_pair rsa_gen_key_pair(long size)
{
    rsa_key_pair key_pair;
    long e = pow(2, size) + 1;
    long p = gen_prime(pow(2, size));
    long q = gen_prime(pow(2, size));
    while (p == q) q = gen_prime(pow(2, size));
    long n = p * q;
    long phi = (p - 1) * (q - 1);
    long d = 0;
    long y = 0;
    eeA(e, phi, &d, &y);
    if (d < 0) d += phi;
    key_pair.pub_key.e = e;
    key_pair.pub_key.n = n;
    key_pair.prv_key.d = d;
    key_pair.prv_key.n = n;


    // printf("e = %d, p = %d, q = %d, n = %d, phi = %d, d = %d, y = %d\n", e, p, q, n, phi, d, y);
    return key_pair;
}

rsa_key_pair rsa_gen_key_pair_p_q(long size, long p, long q)
{
    rsa_key_pair key_pair;
    long e = pow(2, size) + 1;
    while (p == q) q = gen_prime(pow(2, size));
    long n = p * q;
    long phi = (p - 1) * (q - 1);
    long d = 0;
    long y = 0;
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
rsa_key_pair rsa_known_key_pair(long i)
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

long expo_mod(long num, long expo, long mod)
{
    if (expo == 0) return 1;
    long ret = 1;
    for (long i = 0; i < expo; i++)
    {
        ret = (ret * num) % mod;
    }
    return ret;
}

void os2ip(byte *bytes, long *array, int len)
{
    for (int i = 0; i < len; i++) {
        array[i] = bytes[i];
    }
}

void i2osp(long *array, byte *bytes, int len)
{
    for (int i = 0; i < len; i++) {
        bytes[i] = array[i];
    }
}

void enc_rsa(long *plain, long len, long *cipher, rsa_pub_key key)
{
    for (long i = 0; i < len; i++)
    {
        cipher[i] = expo_mod(plain[i], key.e, key.n);
        // printf("%d->%d ", msg[i], enc);
    }
    // printf("\n");
}

void dec_rsa(long *cipher, long len, long *plain, rsa_prv_key key)
{
    for (long i = 0; i < len; i++)
    {
        plain[i] = expo_mod(cipher[i], key.d, key.n);
        // printf("%d->%d ", array[i], array2[i]);
    }
    // printf("\n");
}

void rsa_demo()
{
    long byte_cnt = 16;

    long *rsa_plain = (long *)calloc(byte_cnt, sizeof(long));
    long *rsa_encoded = (long *)calloc(byte_cnt, sizeof(long));
    long *rsa_decoded = (long *)calloc(byte_cnt, sizeof(long));
    byte *bytes = (byte *)calloc(byte_cnt, sizeof(byte));

    // GENERATE RSA KEY PAIR
    rsa_key_pair key_pair;
    key_pair = rsa_known_key_pair(2);
    print_key_pair(key_pair);
    printf("\n");

    // GENERATE PLAINTEXT
    generate_rndm_plaintext(bytes, byte_cnt);
    bytes2longs(bytes, rsa_plain, byte_cnt, key_pair.pub_key);
    printf("PLAIN : ");
    print_bytes(bytes, byte_cnt);
    for (long i = 0; i < byte_cnt; i++) {
        printf("%d ", rsa_plain[i]);
    }
    printf("\n");
    printf("\n"); 

    // ENCRYPT PLAINTEXT
    enc_rsa(rsa_plain, byte_cnt, rsa_encoded, key_pair.pub_key);
    longs2bytes(rsa_encoded, bytes, byte_cnt, key_pair.pub_key);
    printf("CIPHER: ");
    print_bytes(bytes, byte_cnt);
    // print_bytes(encrypted, byte_cnt);
    for (long i = 0; i < byte_cnt; i++) {
        printf("%d ", rsa_encoded[i]);
    }
    printf("\n");
    printf("\n");

    // DECRYPT CIPHERTEXT
    dec_rsa(rsa_encoded, byte_cnt, rsa_decoded, key_pair.prv_key);
    longs2bytes(rsa_decoded, bytes, byte_cnt, key_pair.pub_key);
    printf("PLAIN : ");
    print_bytes(bytes, byte_cnt);
    for (long i = 0; i < byte_cnt; i++) {
        printf("%d ", rsa_decoded[i]);
    }
    printf("\n");
    printf("\n");


    // free some shit
    free(rsa_plain);
    free(rsa_encoded);
    free(rsa_decoded);
}
