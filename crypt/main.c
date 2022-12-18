#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "crypt_util.h"
#include "caesar.h"
#include "vigenere.h"
#include "rsa.h"
#include "rc4.h"
#include "base64.h"
#include "des.h"


int main(int argc, char const *argv[])
{
    // vigenere_demo();
    // rsa_demo();
    // b64_demo();

    des_test();

    return 0;
}
