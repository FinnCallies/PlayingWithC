#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "crypt_util.h"

void print_bytes(byte *bytes, int len) 
{
    for (int i = 0; i < len; i++) {
        printf("%02x ", bytes[i]);
    }
    printf("\n");
}

void print_bytes_by_block(byte *bytes, int len, int block_size)
{
    byte *block = (byte *)calloc(block_size, sizeof(byte));
    printf("\n");

    for (int i = 0; i < len / block_size; i++) {
        memcpy(block, bytes + block_size * (i + 1), block_size);
        printf("Block %d: ", i);
        print_bytes(block, block_size);
    }

    free(block);
}

void gen_rndm_block(byte *block, int len)
{
    for (int i = 0; i < len; i++) {
        block[i] = rand() % 256;
    }
    // print_bytes(block, len);
}

bool is_equal(byte *block1, byte *block2, int len)
{
    for (int i = 0; i < len; i++) {
        if (block1[i] != block2[i]) {
            return false;
        }
    }
    return true;
}

void inc_counter(byte *counter, int len)
{
    if (counter[len - 1] == 255) {
        counter[len - 1] = 0;
        counter[len - 2]++;
    } else {
        counter[len - 1]++;
    }
    
}

void xor_bytes(byte *dest, byte *src1, byte *src2, int len)
{
    for (int i = 0; i < len; i++) {
        dest[i] = src1[i] ^ src2[i];
    }
}
