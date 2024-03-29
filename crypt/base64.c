#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "crypt_util.h"


void print_b64(byte *b64, int len)
{
    for (int i = 0; i < len; i++) {
        printf("%c", b64[i]);
    }
    printf("\n");
}

void print_sextet(byte sextet)
{
    sextet = sextet % 64;
    for (int i = 0; i < 6; i++)
    {
        printf("%d", (sextet >> (5 - i)) & 1);
    }
    printf(" ");
}

void print_sextets(byte *sextets, int len)
{
    for (int i = 0; i < len; i++) {
        print_sextet(sextets[i]);
    }
    printf("\n");
}

int get_padding_size(int octet_cnt) 
{
    return (3 - (octet_cnt % 3)) % 3;
}

int get_padding_from_enc(byte *b64, int len)
{
    int padding = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (b64[i] == '=') {
            padding++;
        } else {
            break;
        }
    }
    return padding;
}

int get_sextet_cnt(int octet_cnt)
{
    return (octet_cnt + get_padding_size(octet_cnt)) / 3 * 4;
}

int get_octet_cnt(byte *b64, int sextet_cnt)
{
    return (sextet_cnt) / 4 * 3 - get_padding_from_enc(b64, sextet_cnt);
}

void octets2sextets(byte *octets, byte *sextets, int len) {
    byte *octets_w_pad = (byte *)calloc(get_sextet_cnt(len), sizeof(byte));

    memcpy(octets_w_pad, octets, len);
    
    int i = 0;
    int j = 0;
    while (i < len) {
        j = i / 3;

        sextets[j * 4] = octets[i] >> 2;
        sextets[j * 4 + 1] = (octets[i] & 0x03) << 6 >> 2 | octets[i + 1] >> 4;
        sextets[j * 4 + 2] = (octets[i + 1] & 0x0f) << 2 | octets[i + 2] >> 6;
        sextets[j * 4 + 3] = octets[i + 2] & 0x3f;

        i += 3;
    }

    free(octets_w_pad);
}

void sextets2octets(byte *sextets, byte *octets, int len)
{
    byte *octets_w_pad = (byte *)calloc(len / 4 * 3, sizeof(byte));

    for (int i = 0; i < len / 4; i++)
    {
        octets_w_pad[i * 3] = sextets[i * 4] << 2 | sextets[i * 4 + 1] >> 4;
        octets_w_pad[i * 3 + 1] = (sextets[i * 4 + 1] & 0x0f) << 4 | sextets[i * 4 + 2] >> 2;
        octets_w_pad[i * 3 + 2] = (sextets[i * 4 + 2] & 0x03) << 6 | sextets[i * 4 + 3];
    }

    memcpy(octets, octets_w_pad, get_octet_cnt(sextets, len));
    
    free(octets_w_pad);
}

void encode_base64(byte *bytes, byte *base64, int len) {
    int padding = get_padding_size(len);
    int sextets_len = get_sextet_cnt(len);
    byte *sextets = (byte *)calloc(sextets_len, sizeof(byte));


    octets2sextets(bytes, sextets, len);

    for (int i = 0; i < len * 4; i++) {
        if (sextets[i] < 26) {
            base64[i] = sextets[i] + 'A';
        } else if (sextets[i] < 52) {
            base64[i] = sextets[i] - 26 + 'a';
        } else if (sextets[i] < 62) {
            base64[i] = sextets[i] - 52 + '0';
        } else if (sextets[i] == 62) {
            base64[i] = '+';
        } else {
            base64[i] = '/';
        }
    }
    for (int i = 0; i < padding; i++) {
        base64[sextets_len - (i + 1)] = '=';
    }

    free(sextets);
}

void decode_base64(byte *base64, byte *bytes, int len)
{
    int padding = get_padding_from_enc(base64, len);
    byte *sextets = (byte *)calloc(len, sizeof(byte));

    for (int i = 0; i < padding; i++) {
        base64[len - i - 1] = 0;
    }

    for (int i = 0; i < len - padding; i++) {
        if (base64[i] == 43) {
            base64[i] = 62;
        } else if (base64[i] == 47) {
            base64[i] = 63;
        } else if (base64[i] > 47 && base64[i] < 58) {
            base64[i] = base64[i] - '0' + 52;
        } else if (base64[i] > 64 && base64[i] < 91) {
            base64[i] = base64[i] - 'A';
        } else if (base64[i] > 96 && base64[i] < 123) {
            base64[i] = base64[i] - 'a' + 26;
        } else {
            printf("ERROR: Invalid character in base64 string\n");
            exit(1);
        }
    }

    sextets2octets(base64, bytes, len);

    free(sextets);
}

void wtf_pls_fix()
{
    byte *plain = "Never gonna give you up, ...";
    int plain_len = 28;
    int enc_len = get_sextet_cnt(plain_len);
    byte *enc = (byte *)calloc(enc_len, sizeof(byte));

    printf("%s\n", plain); // some shit happening, idk, maybe https://www.youtube.com/watch?v=vusV4lF0Epo&t=309s&ab_channel=JacobSorber
    
    encode_base64(plain, enc, plain_len);

    print_b64(enc, enc_len);

    int dec_len = get_octet_cnt(enc, enc_len);
    byte *dec = (byte *)calloc(dec_len, sizeof(byte));

    decode_base64(enc, dec, enc_len);

    print_b64(dec, dec_len);


    free(enc);
    free(dec);
}

void b64_demo()
{
    int byte_cnt = 256;
    int sextet_cnt = get_sextet_cnt(byte_cnt);

    byte *plain = (byte *)calloc(byte_cnt, sizeof(byte));
    byte *encoded = (byte *)calloc(sextet_cnt, sizeof(byte));
    byte *decoded = (byte *)calloc(byte_cnt, sizeof(byte));
    
    gen_rndm_block(plain, byte_cnt);
    printf("PLAINTEXT: \n");
    print_bytes_line_break(plain, byte_cnt, 16);
    printf("\n");

    encode_base64(plain, encoded, byte_cnt);
    printf("ENCODED: \n");
    print_bytes_line_break(encoded, sextet_cnt, 16);
    printf("\n");

    decode_base64(encoded, decoded, sextet_cnt);
    printf("DECODED: \n");
    print_bytes_line_break(decoded, byte_cnt, 16);
    printf("\n");

    if (is_equal(plain, decoded, byte_cnt)) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }


    // free some shit
    free(plain);
    free(encoded);
    free(decoded);
}
