#ifndef POLY_RING_H_
#define POLY_RING_H_


#include <stdbool.h>
#include "crypt_util.h"


typedef unsigned char poly_ring[128];


void poly_ring_init(poly_ring ring);

int get_true_bits(poly_ring ring, int *true_bits, int len);

void block2poly_ring(poly_ring dest, byte *src, int len);

void poly_ring_print(poly_ring ring, int len);

void poly_ring_multiply(poly_ring dest, poly_ring src1, poly_ring src2);

void poly_ring_divide(poly_ring dest, poly_ring src1, poly_ring src2);


#endif // POLY_RING_H_