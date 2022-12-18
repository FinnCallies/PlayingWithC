#ifndef DES_H_
#define DES_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "crypt_util.h"


const int sbox_cnt;
const int block_size;

const byte sbox [8][4][16];

const int key_permutation_table[56];

const int key_rotation_table[16];

const int key_compression_table[48];

const int initial_permutation_table[64];

const int final_permutation_table[64];


void key_permutation(byte *key, byte *shifted_key, int round);

void key_compression(byte *shifted_key, byte *compressed_key);

void key_transformation(byte *key, byte *key_transformed, int round, bool encrypt);

void print_x_bits(byte *x, int n);

void initial_permutation(byte *block, byte *permutated_block);

void expansion_permutation(byte *half_block, byte *expanded_block);

void sbox_permutation(byte *block, byte *sbox_permuted_block);

void pbox_permutation(byte *block, byte *pbox_permuted_block);

void final_permutation(byte *block, byte *final_permuted_block);

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

void des_round(int round, byte *key, byte *rhb, bool encrypt);

void des_function(byte *key, byte *plaintext, byte *ciphertext, bool encrypt);

void des_enc(byte *key, byte *plaintext, byte *ciphertext);

void des_dec(byte *key, byte *ciphertext, byte *plaintext);

void des_test();


#endif // DES_H_