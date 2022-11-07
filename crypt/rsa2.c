#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "crypt_util.h"
#include "rsa2.h"


int ggT(int a, int b)
{
    int r = a % b;
    while (r != 0)
    {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

bool coprime(int a, int b)
{
    int ret;
    ret = ggT(a, b);
    return ret == 1;
}

int phi(int p, int q)
{
    return ((p - 1) * (q - 1));
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

void gen_rsa_key_pair(int p, int q, int *e, int *d, int *n)
{
    int phi_n;
    int k;

    *n = p * q;
    printf("n = %d\n", *n);
    
    phi_n = phi(p, q);
    printf("phi(n) = %d\n", phi_n);
    
    while (!coprime(*e, phi_n)) *e = (rand() + 2) % phi_n;
    *e = 23;
    printf("e = %d\n", *e);
    
    eeA(*e, phi_n, d, &k);
    *d = *d % phi_n;

    printf("d = %d\n", *d);
}

void enc_rsa(byte *plain, int len, int e, int n, byte *cipher)
{
    int i;
    for (i = 0; i < len; i++)
    {
        cipher[i] = (byte) pow(plain[i], e) % n;
    }

    printf("ENCRYPTED PLAINTEXT: ");
    print_bytes(plain, len);
    printf("\n");
    printf("\n");
}

void dec_rsa(byte *cipher, int len, int d, int n, byte *plain)
{
    int i;
    for (i = 0; i < len; i++)
    {
        plain[i] = (byte) pow(cipher[i], d) % n;
    }

    printf("DECRYPTED CIPHERTEXT: ");
    print_bytes(plain, len);
    printf("\n");
    printf("\n");
}
