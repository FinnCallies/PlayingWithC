#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

void print_str_info(char *str)
{
    printf("str: %s\n", str);
    printf("strlen(str): %d\n", strlen(str));
    printf("sizeof(str): %d      just the pointer size...\n", sizeof(str));
    printf("sizeof(char): %d\n", sizeof(char));

    /* for (int i = 0; i < sizeof(str); i++) {
        printf("%d: %c\n", i, str[i]);
    } */
}

int main (int argc, char *argv[]) 
{
    char str[] = "he\0llo\0this\0is\0a\0test\0";

    printf("sizeof(str): %d      this should be the ouput\n", sizeof(str));
    
    print_str_info(str);
}