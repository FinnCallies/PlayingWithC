#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>



void print_help()
{
    printf("Usage: cwatch [OPTION] [ARGUMENT]\n");
    printf("\t-s\t\t\tStart stopwatch\n");
    printf("\t-c [ARGUMENT]\t\tStart countdown\n");
    printf("\t-c [ARGUMENTS] -s\tStart countdown and stop at 00:00\n");
    printf("\t\t[ARGUMENTS] can be in the following formats:\n");
    printf("\t\t\t[MINUTES]:[SECONDS]\n");
    printf("\t\t\t:[SECONDS]\n");
    printf("\t\t\t[MINUTES]:\n");
    printf("\t-h\t\t\tPrint this help\n");
}

void parse_args(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0) {
            time_t start;
            time(&start);
            char string[10];

            time_t now;
            time_t diff;
            while(true) {
                time(&now);
                diff = now - start;
                if (diff % 1 == 0) {
                    strftime(string, 10, "%M:%S", localtime(&diff));
                    printf("\t%s\r", string);
                }
                sleep(0.1);
            }
        } else if (strcmp(argv[i], "-c") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "ERROR: Argument missing\n");
                exit(1);
            } else if (strchr(argv[i + 1], ':') == NULL) {
                fprintf(stderr, "ERROR: Invalid argument\n");
                exit(1);
            }
            
            time_t start;
            char delimiter = ':';
            int minutes = 0;
            int seconds = 0;
            char *ptr = NULL;

            if (strncmp(argv[i + 1], &delimiter, 1) != 0) {
                ptr = strtok(argv[i + 1], &delimiter);
                if (ptr != NULL) {
                    minutes = atoi(ptr);
                    ptr = NULL;
                }
                ptr = strtok(NULL, &delimiter);
                if (ptr != NULL) {
                    seconds = atoi(ptr);
                    ptr = NULL;
                }
            } else if (strlen(argv[i + 1]) == 1) {
                fprintf(stderr, "ERROR: Invalid argument\n");
                exit(1);
            } else {
                ptr = strtok(argv[i + 1], &delimiter);
                if (ptr != NULL) {
                    seconds = atoi(ptr);
                    ptr = NULL;
                }
            }
            i++;
            
            if (i + 1 < argc && strcmp(argv[i + 1], "-s") == 0) {
                time(&start);
                time_t end = start + minutes * 60 + seconds;
                char string[10];

                time_t now;
                time_t diff;
                do {
                    time(&now);
                    diff = end - now;
                    if (diff % 1 == 0) {
                        strftime(string, 10, "%M:%S", localtime(&diff));
                        printf("\r\t%s", string);
                    }
                    sleep(0.01);
                } while(diff != 0);
                printf("\n");
                exit(0);
            } else {
                time(&start);
                time_t end = start + minutes * 60 + seconds;
                char string[10];

                time_t now;
                time_t diff;
                while(true) {
                    time(&now);
                    diff = end - now;
                    if (diff % 1 == 0 && diff >= 0) {
                        strftime(string, 10, "%M:%S", localtime(&diff));
                        printf("\r\t%s", string);
                    } else if (diff % 1 == 0 && diff < 0) {
                        diff = now - end;
                        strftime(string, 10, "%M:%S", localtime(&diff));
                        printf("\r\t-%s", string);
                    }
                    sleep(0.01);
                }
            }
        } else if (strcmp(argv[i], "-h") == 0) {
            print_help();
            exit(0);
        } else {
            fprintf(stderr, "ERROR: Invalid argument\n");
            exit(1);
        }
    }
}

// cwatch -c 1:11
void main(int argc, char *argv[])
{
    parse_args(argc, argv);
}