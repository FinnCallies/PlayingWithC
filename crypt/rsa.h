#ifndef RSA_H_
#define RSA_H_


#include <stdbool.h>

typedef struct {
    long e;
    long n;
} rsa_pub_key;

typedef struct {
    long d;
    long n;
} rsa_prv_key;

typedef struct {
    rsa_prv_key prv_key;
    rsa_pub_key pub_key;
} rsa_key_pair;


void print_key_pair(rsa_key_pair key_pair);

void longs2bytes(long *array, byte *bytes, long len, rsa_pub_key pub_key);

void bytes2longs(byte *bytes, long *array, long len, rsa_pub_key pub_key);

void eeA(long a, long b, long *x, long *y);

rsa_key_pair rsa_gen_key_pair(long size);

rsa_key_pair rsa_gen_key_pair_p_q(long size, long p, long q);

rsa_key_pair rsa_known_key_pair(long i);

long expo_mod(long num, long expo, long mod);

bool isPrime(long n);

long gen_prime(long size);

void enc_rsa(long *plain, long len, long *cipher, rsa_pub_key key);

void dec_rsa(long *cipher, long len, long *plain, rsa_prv_key key);

void rsa_demo();


#endif // RSA_H_
