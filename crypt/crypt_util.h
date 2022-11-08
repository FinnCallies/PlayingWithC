#ifndef CRYPT_UTIL_H_
#define CRYPT_UTIL_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef unsigned char byte;


void print_bytes(byte *bytes, int len);

void print_bytes_by_block(byte *bytes, int len, int block_size);

void generate_rndm_plaintext(byte *plaintext, int len);

void gen_rndm_block(byte *block, int len);

bool is_equal(byte *block1, byte *block2, int len);

void inc_counter(byte *counter, int len);

void xor_bytes(byte *dest, byte *src1, byte *src2, int len);


#endif // CRYPT_UTIL_H_