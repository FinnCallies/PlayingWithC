#ifndef VIGENERE_H_
#define VIGENERE_H_


#include "crypt_util.h"


void enc_vigenere(byte *plain, int len, byte *key, int key_len, byte *cipher);

void dec_vigenere(byte *cipher, int len, byte *key, int key_len, byte *plain);

void enc_vigenere_ecb(byte *plain, int len, byte *key, byte *cipher, int block_size);

void dec_vigenere_ecb(byte *cipher, int len, byte *key, byte *plain, int block_size);

void enc_vigenere_cbc(byte *plain, int len, byte *key, byte *cipher, byte *iv, int block_size, bool logs);

void dec_vigenere_cbc(byte *cipher, int len, byte *key, byte *plain, byte *iv, int block_size, bool logs);

void enc_vigenere_ctr(byte *plain, int len, byte *key, byte *cipher, byte *iv, int block_size);

void dec_vigenere_ctr(byte *cipher, int len, byte *key, byte *plain, byte *iv, int block_size);

void vigenere_demo();


#endif // VIGENERE_H_