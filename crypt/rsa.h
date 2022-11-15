#ifndef RSA_H_
#define RSA_H_


#include <stdbool.h>

typedef struct {
    int e;
    int n;
} rsa_pub_key;

typedef struct {
    int d;
    int n;
} rsa_prv_key;

typedef struct {
    rsa_prv_key prv_key;
    rsa_pub_key pub_key;
} rsa_key_pair;


void print_key_pair(rsa_key_pair key_pair);

void eeA(int a, int b, int *x, int *y);

rsa_key_pair rsa_gen_key_pair(int size);

rsa_key_pair rsa_gen_key_pair_p_q(int size, int p, int q);

rsa_key_pair rsa_known_key_pair(int i);

int expo_mod(int num, int expo, int mod);

bool isPrime(int n);

int gen_prime(int size);

void enc_rsa(int *plain, int len, int *cipher, rsa_pub_key key);

void dec_rsa(int *cipher, int len, int *plain, rsa_prv_key key);

void rsa_demo();


#endif // RSA_H_
