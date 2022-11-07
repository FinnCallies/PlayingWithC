#include "crypt_util.h"
#include <stdbool.h>
#include <math.h>
#include <string.h>


bool is_prime(double v) 
{
    if (v < 2) return false;

    for (int i = 2; i <= sqrt(v); i++) {
        if ((int) v % i == 0) return false;
    }

    return true;
}

double get_primes(double least_significant, double most_significant, double *ret) 
{
    double *list = (double *) calloc(most_significant/log2(most_significant), sizeof(double));
    int index = 0;
    if (least_significant < 2) least_significant = 2;
    
    printf("listing primes between %lf and %lf:\n", least_significant, most_significant);
    for (double i = least_significant; i < most_significant; i++) {
        if (is_prime(i)) {
            list[index] = i;
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

void gen_p_q(double *p, double *q, double l, double m)
{
    printf("log2(%lf) = %lf\n", m, log2(m));
    double *primes = (double *) calloc((m/log2(m)), sizeof(double));
    printf("primes init\n");
    int prime_cnt = get_primes(log2(m), m, primes);
    printf("primes calculated\n");
    
    *p = primes[rand() % prime_cnt];
    int r = rand();
    printf("r = %d; cnt = %d\n", r, prime_cnt);
    printf("p = %lf\n", *p);
    do {
        *q = primes[rand() % prime_cnt];
    } while (!is_coprime(*p, *q));
}

void eeA(double a, double b, double *x, double *y)
{
    
}

void generate_rsa_key_pair()
{
    double l, m = 0;
    l = pow(2, 4); // 2^16
    m = pow(2, 8); // 2^32
    int e = l + 1;
    printf("e = %d, m = %lf, l = %lf\n", e, m, l);
    double p, q = 0;
    gen_p_q(&p, &q, l, m);
    printf("q = %lf\n", q);
    double n = p * q;
    double phi = (p - 1) * (q - 1);

    if (is_coprime(e, phi)) {
        printf("e and phi are coprime\n");
    } else {
        printf("e and phi are not coprime\n");
    }

    printf("n = %lf, phi(n) = %lf\n", n, phi);
}
