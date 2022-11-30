#ifndef DES_H_
#define DES_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypt_util.h"


const int sbox_cnt;

const byte s1[4][16];

const byte s2[4][16];

const byte s3[4][16];

const byte s4[4][16];

const byte s5[4][16];

const byte s6[4][16];

const byte s7[4][16];

const byte s8[4][16];

const int key_permutation_table[56];

const int key_rotation_table[16];

const int key_compression_table[48];


void print_x_bits(byte *x, int n);

void expand_block(byte *half_block, int half_block_size, byte *expanded_block);

void expansion(byte *block, int len, int block_size, byte *expanded_block);

void drop_parity_bits(byte *supplied_key, byte *sub_key);

void permutate_key(byte *supplied_key, byte *permutated_key);

void permutation(byte *block, const int *permutation_table, int table_size, byte *permutated_block);

void bit_rotation(byte *permutated_key, int rnd, byte *rotated_key);

void compress_key(byte *rotated_key, byte *compressed_key);

void key_schedule(byte *supplied_key, byte **sub_keys);

void feistel(byte *block, byte *supplied_key, byte **sub_keys);

void des_demo_constructed(byte *block, byte *supplied_key);

void des_demo();


#endif // DES_H_