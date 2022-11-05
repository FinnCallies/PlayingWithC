#include "poly_ring.h"
#include "crypt_util.h"


void poly_ring_init(poly_ring ring)
{
    for (int i = 0; i < 128; i++) {
        ring[i] = 0;
    }

    ring[0] = 1;
    ring[1] = 1;
    ring[2] = 1;
    ring[7] = 1;
    ring[128] = 1;
}

int get_true_bits(poly_ring ring, int *true_bits, int *len)
{
    int j = 0;
    for (int i = 127; i >= 0; i--) {
        if (ring[i]) {
            true_bits[j] = i;
            j++;
        }
    }
    return j;
}

void block2poly_ring(poly_ring dest, byte *src, int len)
{
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < 8; j++) {
            dest[i * 8 + j] = (src[i] >> j) & 1;
        }
    }
}

void poly_ring_print(poly_ring ring)
{
    int *true_bits = (int *)calloc(128, sizeof(int));
    int true_bits_len = get_true_bits(ring, true_bits, 128);

    for (int i = 0; i < true_bits_len; i++) {
        printf("a^%d", true_bits[i]);
        if (i != true_bits_len - 1) {
            printf(" + ");
        }
    }
    printf("\n");

    free(true_bits);
}

void poly_ring_multiply(poly_ring dest, poly_ring src1, poly_ring src2)
{
    for (int i = 0; i < 128; i++) {
        for (int j = 0; j < 128; j++) {
            dest[j] = (dest[j] + (src1[i] * src2[j])) % 2;
        }
    }
}

void poly_ring_divide(poly_ring dest, poly_ring src1, poly_ring src2)
{
    int *true_bits = (int *)calloc(128, sizeof(int));
    int true_bits_len = get_true_bits(src2, true_bits, 128);

    for (int i = 0; i < 128; i++) {
        dest[i] = src1[i];
    }

    for (int i = 0; i < 128; i++) {
        if (dest[i]) {
            for (int j = 0; j < true_bits_len; j++) {
                dest[i + true_bits[j]] = (dest[i + true_bits[j]] + 1) % 2;
            }
        }
    }
}
