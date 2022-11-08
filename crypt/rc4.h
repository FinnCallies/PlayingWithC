#ifndef RC4_H_
#define RC4_H_

#include <stdbool.h>
#include "crypt_util.h"

void construct_key_from_sbox(byte *sbox, int block_size, byte *key);
void ksa(byte *key, int key_len, byte *sbox, int block_size, bool construct_key);
void generate_keystream(byte *key, int key_len, int block_size, byte *keystream);
void enc_rc4(byte *plaintext, int len, byte *keystream, int block_size, byte *ciphertext);
void dec_rc4(byte *ciphertext, int len, byte *keystream, int block_size, byte *plaintext);

#endif // RC4_H_