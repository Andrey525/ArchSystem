#include "dgemm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help() {
    printf("Incorrect input of arguments!\n"
           "Use, for example: ./dgemm --size 2048\n");
}

int getSize(int argc, char *argv[]) {
    int size;
    if (argc == 3) {
        if (strcmp(argv[1], "--size") == 0) {
            int num_count = 0;
            for (int i = 0; i < strlen(argv[2]); i++) {
                if (argv[2][i] >= '0' && argv[2][i] <= '9') {
                    num_count++;
                }
            }
            if (num_count == strlen(argv[2])) {
                size = atoi(argv[2]);
            } else {
                help();
                return -1;
            }
        } else {
            help();
            return -1;
        }
    } else {
        help();
        return -1;
    }
    return size;
}

int main(int argc, char *argv[]) {
    const int n = getSize(argc, argv);
    if (!n) {
        return -1;
    }
    printf("%d\n", n);
    return 0;
}