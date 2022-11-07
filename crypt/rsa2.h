#ifndef RSA2_H
#define RSA2_H


#include "crypt_util.h"
#include <stdbool.h>


int ggT(int a, int b);

bool coprime(int a, int b);

int phi(int p, int q);

void eeA(int a, int b, int *x, int *y);

void gen_rsa_key_pair(int p, int q, int *e, int *d, int *n);

void enc_rsa(byte *plain, int len, int e, int n, byte *cipher);

void dec_rsa(byte *cipher, int len, int d, int n, byte *plain);


#endif // RSA2_H