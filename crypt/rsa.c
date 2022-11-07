#include "crypt_util.h"
#include <stdbool.h>
#include <math.h>
#include <string.h>


bool is_prime(double v) 
{
    for (int i = 2; i < sqrt(v); i++) {
        if (fmod(v, i) != 0)
            return false;
    }
    return true;
}

double get_primes(double least_significant, double most_significant, double *ret) 
{
    double *list = (double *) calloc(most_significant/log(most_significant), sizeof(double));
    int index = 0;
    if (least_significant < 2) least_significant = 2;
    
    for (double i = least_significant; i < most_significant; i++) {
        if (is_prime(most_significant))
        {
            list[index] = most_significant;
            index++;
        }
    }
    memcpy(ret, list, index);
    return index;
}

double gcd(double a, double b) 
{
    double x;
    if (a == 0) return a;
    if (b == 0) return b;

    do {
        x = fmod(a, b);
        a = b;
        b = x;
    } while (b != 0);
    
    return abs(a);
}

double get_prndm_prime(double least_significant, double most_significant)
{
    double *primes = (double *) calloc((most_significant/log(most_significant)) - (least_significant/log(least_significant)), sizeof(double));
    int prime_cnt = get_primes(least_significant, most_significant, primes);
    return primes[rand() % prime_cnt];
}

bool is_coprime(double a, double b)
{
    if (gcd(a, b) == 1) return true;
    return false;
}

int get_coprimes(int *prime_list, int len, int v, int *coprime_list)
{
    int index = 0;
    for (int i = 0; i < len; i++)
    {
        if (is_coprime(prime_list[i], v))
        {
            coprime_list[index] = prime_list[i];
            index++;
        }
    }
    return index;
}

void gen_p_q(double *p, double *q)
{
    double *primes = (double *) calloc(((pow(2, 32))/log(pow(2, 32))), sizeof(double));
    int prime_cnt = get_primes(pow(2, 8), pow(2, 32), primes);
    *p = primes[rand() % prime_cnt];
    printf("p = %d\n", *p);
    do {
        *q = primes[rand() % prime_cnt];
    } while (!is_coprime(*p, *q));
}

void generate_rsa_key_pair()
{
    int e = pow(2, 16) + 1;
    printf("e = %d\n", e);
    double p, q = 0;
    gen_p_q(&p, &q);
    printf("q = %d\n", q);
    int n = p * q;
    int phi = (p - 1) * (q - 1);

    printf("n = %d, phi(n) = %d\n", n, phi);
}
