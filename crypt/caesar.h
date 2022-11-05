#ifndef CAESAR_H_
#define CAESAR_H_


#include "crypt_util.h"


void enc_caesar(byte *plain, int len, int key, byte *cipher);

void dec_caesar(byte *cipher, int len, int key, byte *plain);


#endif // CAESAR_H_