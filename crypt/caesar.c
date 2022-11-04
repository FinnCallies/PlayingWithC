#include "crypt_util.h"
#include "caesar.h"


void enc_caesar(byte *plain, int len, int key, byte *cipher)
{   
    for (int i = 0; i < len; i++)
        cipher[i] = (plain[i] + key) % 256;
}

void dec_caesar(byte *cipher, int len, int key, byte *plain)
{
    for (int i = 0; i < len; i++)
        plain[i] = (cipher[i] - key) % 256;
}
