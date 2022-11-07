#ifndef RSA_H_
#define RSA_H_

#include <stdbool.h>

bool is_prime(int v);
double get_primes(double least_significant, double most_significant, double *ret);
double gcd(double a, double b);
double get_prndm_prime(double least_significant, double most_significant);
bool is_coprime(double a, double b);
int get_coprimes(int *prime_list, int len, int v, int *coprime_list);
void gen_p_q(double *p, double *q, double l, double m);
void generate_rsa_key_pair();

#endif // RSA_H_
