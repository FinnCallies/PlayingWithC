#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "des.h"
#include "crypt_util.h"


const int sbox_cnt = 8;
const int block_size = 64;

const byte sbox[8][4][16] = {
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};

const int pbox[32] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25
};

const int key_permutation_table[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

const int key_rotation_table[16] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

const int key_compression_table[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

const int initial_permutation_table[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

const int final_permutation_table[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};


void key_permutation(byte *key, byte *shifted_key, int round)
{
    byte *key_left = (byte *)calloc(4, sizeof(byte));
    byte *key_right = (byte *)calloc(4, sizeof(byte));

    /* memcpy(key_left, key, 4);
    memcpy(key_right, key + 3, 4); */

    for (int i = 0; i < 28; i++) {
        key_left[i / 8] |= ((key[(key_permutation_table[i] - 1) / 8] >> (7 - (key_permutation_table[i] - 1) % 8)) & 1) << (7 - i % 8);
    }
    for (int i = 0; i < 28; i++) {
        key_right[i / 8] |= ((key[(key_permutation_table[i] - 1) / 8] >> (7 - (key_permutation_table[i] - 1) % 8)) & 1) << (7 - i % 8);
    }


    printf("key_left before shift : ");
    print_bytes_binary(key_left, 4);
    printf("key_right before shift: ");
    print_bytes_binary(key_right, 4);


    for (int j = 1; j <= round; j++) {
        int shift = key_rotation_table[j - 1];
        byte shift_byte = 0;
        if (shift == 2) {
            shift_byte = 3;
        } else {
            shift_byte = 1;
        }

        // left half
        byte overflow_old = (key_left[0] >> (8 - shift)) & shift_byte;
        for (int i = 3; i >= 0; i--) {
            byte overflow_new = (key_left[i] >> (8 - shift)) & shift_byte;
            if (i == 3) {
                key_left[i] = key_left[i] << shift | (overflow_old << 4);
            } else {
                key_left[i] = key_left[i] << shift | overflow_old;
            }
            overflow_old = overflow_new;
        }
        key_left[3] &= 0xF0;

        // right half
        overflow_old = (key_right[0] >> 4 - shift) & shift_byte;
        for (int i = 3; i >= 0; i--) {
            byte overflow_new = (key_right[i] >> (8 - shift)) & shift_byte;
            key_right[i] = key_right[i] << shift | overflow_old;
            overflow_old = overflow_new;
        }
        key_right[0] &= 0x0F;
    }


    printf("Left half after shift : ");
    print_bytes_binary(key_left, 4);
    printf("Right half after shift: ");
    print_bytes_binary(key_right, 4);

    // combine left and right half
    memcpy(shifted_key, key_left, 4);
    memcpy(shifted_key + 4, key_right + 1, 3);
    shifted_key[3] |= key_right[0];

    free(key_left);
    free(key_right);
}

void key_compression(byte *shifted_key, byte *compressed_key)
{
    for (int i = 0; i < 48; i++) {
        int index = key_compression_table[i] - 1;
        int byte_index = index / 8;
        int bit_index = index % 8;
        byte bit = (shifted_key[byte_index] >> (7 - bit_index)) & 1;
        compressed_key[i / 8] |= bit << (7 - i % 8);
    }
}

void key_transformation(byte *key, byte *key_transformed, int round, bool encrypt)
{
    byte *shifted_key = (byte *)calloc(7, sizeof(byte));
    if (encrypt) {
        key_permutation(key, shifted_key, round);
    } else {
        key_permutation(key, shifted_key, 17 - round);
    }
    
    // key_permutation(key, shifted_key, round);

    key_compression(shifted_key, key_transformed);

    free(shifted_key);
}

void print_x_bits(byte *x, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        printf("%d", (x[i / 8] >> (7 - i % 8)) & 1);
    }
    printf(" ");
}

void initial_permutation(byte *plain_block, byte *permuted_block)
{
    for (int i = 0; i < block_size; i++) {
        permuted_block[i / 8] |= ((plain_block[(initial_permutation_table[i] - 1) / 8] >> (7 - (initial_permutation_table[i] - 1) % 8)) & 1) << (7 - i % 8);
    }
}

void expansion_permutation(byte *half_block, byte *expanded_block)
{
    int pos = 0;
    byte leading_bit = 0;
    byte trailing_bit = 0;
    int shift = 0;
    for (int i = 0; i < 8; i++) {
        byte b = 0;

        if (i % 2 == 0) {
            shift = 7;
            if (i == 0) {
                leading_bit = (half_block[3] >> 7) & 1;
            } else {
                leading_bit = (half_block[i - 1] >> 7) & 1;
            }
            trailing_bit = (half_block[i] >> 3) & 1;
        } 
        else {
            shift = 3;
            if (i == 7) {
                trailing_bit = (half_block[0] >> 7) & 1;
            } else {
                trailing_bit = (half_block[i + 1] >> 3) & 1;
            }
            leading_bit = (half_block[i] >> 4) & 1;
        }
        
        expanded_block[pos / 8] |= (leading_bit << (7 - pos % 8));
        pos++;
        for (int j = 0; j < 4; j++) {
            expanded_block[pos / 8] |= ((half_block[i] >> (shift - j)) & 1) << (7 - pos % 8);
            pos++;
        }
        expanded_block[pos / 8] |= (trailing_bit << (7 - pos % 8));
        pos++;
    }
}

void sbox_permutation(byte *block, byte *sbox_permuted_block)
{
    int pos = 0;
    for (int i = 0; i < 8; i++) {
        int row = ((block[i * 6] >> 7 - ((i * 6) % 8) << 1) & 2) | ((block[i * 6 + 5] >> 7 - ((i * 6 + 5) % 8)) & 1);
        int col = ((block[i * 6 + 1] >> 7 - ((i * 6 + 1) % 8) << 3) & 8)
                | ((block[i * 6 + 2] >> 7 - ((i * 6 + 2) % 8) << 2) & 4)
                | ((block[i * 6 + 3] >> 7 - ((i * 6 + 3) % 8) << 1) & 2)
                | ((block[i * 6 + 4] >> 7 - ((i * 6 + 4) % 8)) & 1);
        byte value = sbox[i][row][col];
        if (i % 2 == 0) {
            sbox_permuted_block[i / 2] |= value << 4;
        } else {
            sbox_permuted_block[i / 2] |= value;
        }
    }
}

void pbox_permutation(byte *block, byte *pbox_permuted_block)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            pbox_permuted_block[i] |= ((block[(pbox[i * 8 + j] - 1) / 8] >> (7 - ((pbox[i * 8 + j] - 1) % 8))) & 1) << (7 - j);
        }
    }
}

void final_permutation(byte *block, byte *final_permuted_block)
{
    for (int i = 0; i < block_size; i++) {
        final_permuted_block[i / 8] |= ((block[(final_permutation_table[i] - 1) / 8] >> (7 - ((final_permutation_table[i] - 1) % 8))) & 1) << (7 - i % 8);
    }
}


void expand_block(byte *half_block, int half_block_size, byte *expanded_block)
{
    byte left;
    byte right;
    // byte *expanded_block = (byte *)calloc(half_block_size + half_block_size / 2, sizeof(byte));
    printf("half_block            : ");
    print_bytes_binary(half_block, half_block_size);
    int i, j;
    for (i = 0; i < half_block_size; i++)
    {
        // print_byte_binary(half_block[i]);
        if (i == 0) {
            left = half_block[half_block_size - 1] << 5 & 0x20;
        } else {
            left = half_block[i - 1] << 5 & 0x20;
        }
        left = left | (half_block[i] >> 3 & 0x1e);
        left = left | (half_block[i] >> 3 & 0x01);


        right = half_block[i] << 1 & 0x20;
        right = right | (half_block[i] << 1 & 0x1e);
        if (i == half_block_size - 1) {
            right = right | (half_block[0] >> 7 & 0x01);
        } else {
            right = right | (half_block[i + 1] >> 7 & 0x01);
        }
        /* printf("left: ");
        print_byte_binary(left);
        printf("right: ");
        print_byte_binary(right);
        printf("\n"); */


        expanded_block[i * 2] = left;
        expanded_block[i * 2 + 1] = right;
    }
    

    // print_bytes_binary(expanded_block, half_block_size + half_block_size / 2);

    /* for (int i = 0; i < half_block_size/4; i++)
    {
        if (i == 0) {
            expanded_block[i] = half_block[half_block_size - 1];
        } else {
            expanded_block[i * 6] = half_block[i * 4 - 1];
        }
        memcpy(expanded_block + i * 6 + 1, half_block + i * 4, 4);
        if (i == half_block_size/4 - 1) {
            expanded_block[i * 6 + 5] = half_block[0];
        } else {
            expanded_block[i * 6 + 5] = half_block[(i + 1) * 4];
        }
    } */
}

void expansion(byte *block, int block_cnt, int block_size, byte *expanded_block) 
{
    int half_block_size = block_size / 2;
    for (int i = 0; i < block_cnt * 2; i++) {
        expand_block(block + i * half_block_size, half_block_size, expanded_block + i * (half_block_size + half_block_size / 2));
        printf("expanded_block %d: ", i);
        for (int j = 0; j < half_block_size + half_block_size / 2; j++) {
            printf("%d ", expanded_block[i * (half_block_size + half_block_size / 2) + j]);
        }
    }
}

void drop_parity_bits(byte *supplied_key, byte *sub_key)
{
    memcpy(sub_key, supplied_key, 7);

    for (int i = 0; i < 7; i++) {
        sub_key[i] = sub_key[i] << i;

        byte b = 0xff;
        b = b << i + 1;

        sub_key[i] = sub_key[i] & b;

        b = supplied_key[i + 1] >> (8 - (i + 1));

        sub_key[i] = sub_key[i] | b;
    }
}

void permutate_key(byte *supplied_key, byte *permutated_key)
{
    for (int i = 0; i < 56; i++) {
        byte b = 0;
        int pos = 0;
        int byte_idx = 0;
        int bit_idx = 0;

        pos = key_permutation_table[i];

        byte_idx = pos / 8;
        bit_idx = pos % 8;

        b = supplied_key[byte_idx] >> (7 - bit_idx + 1);
        b = b & 1;
        b = b << (7 - i % 8);

        permutated_key[i / 8] = permutated_key[i / 8] | b;
        
        /* printf("pos: %d, byte_idx: %d, bit_idx: %d, b: %d, ", pos, byte_idx, bit_idx, b);
        print_bytes_binary(&b, 1);
        print_bytes_binary(permutated_key, 7); */
    }
    /* printf("permutated key: ");
    print_bytes_binary(permutated_key, 7); */
}

void permutation(byte *block, const int *permutation_table, int table_size, byte *permutated_block)
{
    for (int i = 0; i < table_size; i++) {
        byte b = 0;
        int pos = 0;
        int byte_idx = 0;
        int bit_idx = 0;

        pos = permutation_table[i];

        byte_idx = pos / 8;
        bit_idx = pos % 8;

        b = block[byte_idx] >> (7 - bit_idx + 1);
        b = b & 1;
        b = b << (7 - i % 8);

        permutated_block[i / 8] = permutated_block[i / 8] | b;
        
        /* printf("pos: %d, byte_idx: %d, bit_idx: %d, b: %d, ", pos, byte_idx, bit_idx, b);
        print_bytes_binary(&b, 1);
        print_bytes_binary(permutated_block, 8); */
    }
}

void bit_rotation(byte *permutated_key, int rnd, byte *rotated_key)
{
    byte *l = (byte *)calloc(4, sizeof(byte));
    byte *r = (byte *)calloc(4, sizeof(byte));

    memcpy(l, permutated_key, 4);
    memcpy(r, permutated_key + 3, 4);

    for (int i = 0; i < 4; i++) {
        l[i] = l[i] << key_rotation_table[rnd];
        if (i < 3) {
            l[i] = l[i] | (l[i + 1] >> (8 - key_rotation_table[rnd]));
        } else {
            l[i] = l[i] | ((permutated_key[0] >> 4 - key_rotation_table[rnd]) & 0x30);
            l[i] = l[i] & 0xf0;
        }        
    }

    for (int i = 0; i < 4; i++) {
        r[i] = r[i] << key_rotation_table[rnd];
        if (i < 3) {
            r[i] = r[i] | (r[i + 1] >> (8 - key_rotation_table[rnd]));
        } else {
            r[i] = r[i] | ((permutated_key[3] >> 4 - key_rotation_table[rnd]) & 0x03);
            r[0] = r[0] & 0x0f;
        }        
    }

    memcpy(rotated_key, l, 3);
    memcpy(rotated_key + 4, r + 1, 3);
    rotated_key[3] = l[3] | r[0];
    

    /* printf("l: ");
    print_bytes_binary(l, 4);
    printf("r: ");
    print_bytes_binary(r, 4); */

    free(l);
    free(r);
}

void compress_key(byte *rotated_key, byte *compressed_key)
{
    for (int i = 0; i < 48; i++) {
        byte b = 0;
        int pos = 0;
        int byte_idx = 0;
        int bit_idx = 0;

        pos = key_compression_table[i];

        byte_idx = (pos - 1) / 8;
        bit_idx = (pos - 1) % 8;

        b = rotated_key[byte_idx] >> (7 - bit_idx);
        b = b & 1;
        b = b << (7 - i % 8);

        compressed_key[i / 8] = compressed_key[i / 8] | b;
        
        /* printf("i: %d, pos: %d, byte_idx: %d, bit_idx: %d, b: %d, ", i, pos, byte_idx, bit_idx, b);
        print_bytes_binary(&b, 1); */
    }
}

void key_schedule(byte *supplied_key, byte **sub_keys)
{
    byte *sub_key = (byte *)calloc(7, sizeof(byte));
    printf("supplied key          : ");
    print_bytes_binary(supplied_key, 8);
    drop_parity_bits(supplied_key, sub_key);
    printf("dropped parity bits   : ");
    print_bytes_binary(sub_key, 7);




    byte *permutated_key = (byte *)calloc(7, sizeof(byte));
    // permutate_key(supplied_key, permutated_key);
    permutation(supplied_key, key_permutation_table, 56, permutated_key);
    printf("permutated key        : ");
    print_bytes_binary(permutated_key, 7);


    byte *rotated_key = (byte *)calloc(7, sizeof(byte));
    bit_rotation(permutated_key, 0, rotated_key);
    printf("rotated key           : ");
    print_bytes_binary(rotated_key, 7);
    
    
    byte *compressed_key = (byte *)calloc(6, sizeof(byte));
    // compress_key(rotated_key, compressed_key);
    permutation(rotated_key, key_compression_table, 48, compressed_key);
    printf("compressed key        : ");
    print_bytes_binary(compressed_key, 6);

    // bits cut out: 9 18 22 25 35 38 43 54

    /* cnt_high_bits(compressed_key, 6);
    printf("cnt: %d\n", cnt_high_bits(compressed_key, 6));
    cnt_high_bits(rotated_key, 7);
    printf("cnt: %d\n", cnt_high_bits(rotated_key, 7)); */




    free(sub_key);
    free(permutated_key);
    free(rotated_key);
    free(compressed_key);
}

void feistel(byte *block, byte *supplied_key, byte **sub_keys)
{
    int block_size = 8;
    int half_block_size = block_size / 2;
    int expanded_half_block_size = half_block_size * 2;

    byte *l_block = (byte *)calloc(half_block_size, sizeof(byte));
    byte *r_block = (byte *)calloc(half_block_size, sizeof(byte));
    byte *expanded_block = (byte *)calloc(expanded_half_block_size, sizeof(byte));
    byte *after_sbox = (byte *)calloc(half_block_size, sizeof(byte));

    memcpy(l_block, block, half_block_size);
    memcpy(r_block, block + half_block_size, half_block_size);

    expand_block(r_block, half_block_size, expanded_block);

    printf("block_after_epansion  : ");
    print_bytes_binary(expanded_block, expanded_half_block_size);
    printf("\n");

    free(l_block);
    free(r_block);
    free(expanded_block);
    free(after_sbox);
}

void des_demo_constructed(byte *block, byte *supplied_key)
{
    byte **sub_keys = (byte **)calloc(16, sizeof(byte *));

    printf("block                 : ");
    print_bytes_binary(block, 8);
    printf("block as string       : ");
    printf("%s\n", block);

    key_schedule(supplied_key, sub_keys);
    feistel(block, supplied_key, sub_keys);

    for (int i = 0; i < 16; i++) {
        free(sub_keys[i]);
    }
}

void des_demo() 
{
    byte **sub_keys = (byte **)calloc(16, sizeof(byte *));
    for (int i = 0; i < 16; i++) {
        sub_keys[i] = (byte *)calloc(6, sizeof(byte));
    }

    int block_size = 8;

    byte *block = (byte *)calloc(block_size, sizeof(byte));

    gen_rndm_block(block, block_size);
    printf("block                 : ");
    print_bytes_binary(block, block_size);
    /* printf("block as string       : ");
    printf("%s\n", block); */


    byte *supplied_key = (byte *)calloc(8, sizeof(byte));
    gen_rndm_block(supplied_key, 8);

    key_schedule(supplied_key, sub_keys);
    feistel(block, supplied_key, sub_keys);


    free(block);
    free(supplied_key);
    for (int i = 0; i < 16; i++) {
        free(sub_keys[i]);
    }
}

void des_round(int round, byte *key, byte *rhb, bool encrypt)
{
    byte *key_transformed = (byte *)calloc(6, sizeof(byte));
    byte *expanded_rhb = (byte *)calloc(6, sizeof(byte));
    byte *xored_rhb = (byte *)calloc(6, sizeof(byte));
    byte *sbox_rhb = (byte *)calloc(4, sizeof(byte));
    byte *pbox_rhb = (byte *)calloc(4, sizeof(byte));


    printf("round %d: \n", round);
    key_transformation(key, key_transformed, round, encrypt);
    printf("key_transformed       : ");
    print_bytes_binary(key_transformed, 6);

    expansion_permutation(rhb, expanded_rhb);
    printf("expanded_rhb          : ");
    print_bytes_binary(expanded_rhb, 6);

    xor_bytes(xored_rhb, key_transformed, expanded_rhb, 6);
    printf("xored_rhb             : ");
    print_bytes_binary(xored_rhb, 6);

    sbox_permutation(xored_rhb, sbox_rhb);
    printf("sbox_rhb              : ");
    print_bytes_binary(sbox_rhb, 4);

    pbox_permutation(sbox_rhb, pbox_rhb);
    printf("pbox_rhb              : ");
    print_bytes_binary(pbox_rhb, 4);


    free(key_transformed);
    free(expanded_rhb);
    free(xored_rhb);
    free(sbox_rhb);
    free(pbox_rhb);
}

void des_function(byte *key, byte *plaintext, byte *ciphertext, bool encrypt)
{
    byte *init_permutation = (byte *)calloc(8, sizeof(byte));
    byte *lhb = (byte *)calloc(4, sizeof(byte));
    byte *rhb = (byte *)calloc(4, sizeof(byte));
    byte *key_dropped_parity = (byte *)calloc(7, sizeof(byte));
    byte *key_transformed = (byte *)calloc(6, sizeof(byte));
    byte *expanded_rhb = (byte *)calloc(6, sizeof(byte));
    byte *xored_rhb = (byte *)calloc(6, sizeof(byte));
    byte *sbox_rhb = (byte *)calloc(4, sizeof(byte));
    byte *pbox_rhb = (byte *)calloc(4, sizeof(byte));
    byte *joined = (byte *)calloc(8, sizeof(byte));
    byte *fin_permutation = (byte *)calloc(8, sizeof(byte));


    print_x_bits(plaintext, block_size);
    initial_permutation(plaintext, init_permutation);
    print_x_bits(init_permutation, block_size);
    printf("\n");

    memcpy(lhb, init_permutation, 4);
    memcpy(rhb, init_permutation + 4, 4);
    printf("lhb: ");
    print_bytes_binary(lhb, 4);
    printf("rhb: ");
    print_bytes_binary(rhb, 4);

    printf("key 64 bit            : ");
    print_bytes_binary(key, 8);
    drop_parity_bits(key, key_dropped_parity);
    printf("key 56 bit            : ");
    print_bytes_binary(key_dropped_parity, 7);

    for (int round = 1; round <= 16; round++) {
        des_round(round, key, rhb, encrypt);

        memcpy(lhb, rhb, 4);
        xor_bytes(rhb, lhb, pbox_rhb, 4);
    }
    memcpy(joined, lhb, 4);
    memcpy(joined + 4, rhb, 4);
    printf("joined                : ");
    print_bytes_binary(joined, 8);

    final_permutation(joined, fin_permutation);
    printf("final_permutation     : ");
    print_bytes_binary(fin_permutation, 8);


    free(init_permutation);
    free(lhb);
    free(rhb);
    free(expanded_rhb);
    free(xored_rhb);
    free(sbox_rhb);
    free(pbox_rhb);
    free(joined);
    free(fin_permutation);
}

void des_enc(byte *key, byte *plaintext, byte *ciphertext)
{
    des_function(key, plaintext, ciphertext, true);
}

void des_dec(byte *key, byte *ciphertext, byte *plaintext)
{
    des_function(key, ciphertext, plaintext, false);
}

/* 


    init permutation
    drop parity bits
    LHB RHB
    16 rounds with LHB RHB
        key transformation
        expansion permutation
        s-box
        p-box
        XOR and swap
    final permutation

*/
void des_test() {
    byte *cipher_block = (byte *)calloc(8, sizeof(byte));
   
    byte block[8] = "Hello Wo";

    byte key[8] = {0x34, 0x2d, 0xb5, 0xa8, 0x1d, 0xdb, 0x90, 0x04};


    des_enc(key, block, cipher_block);

    // des_dec(key, cipher_block, block);


    free(cipher_block);
}
