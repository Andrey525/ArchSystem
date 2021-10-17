#include "dgemm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

void help() {
    printf("Incorrect input of arguments!\n"
           "Use, for example: ./dgemm --size 2048\n");
}

double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getSize(int argc, char *argv[]) {
    int size;
    if (argc == 3 || argc == 5) {
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

int getBS(int argc, char *argv[]) {
    int BS;
    if (argc == 5) {
        if (strcmp(argv[3], "--block-size") == 0) {
            int num_count = 0;
            for (int i = 0; i < strlen(argv[4]); i++) {
                if (argv[4][i] >= '0' && argv[4][i] <= '9') {
                    num_count++;
                }
            }
            if (num_count == strlen(argv[4])) {
                BS = atoi(argv[4]);
            } else {
                help();
                return -1;
            }
        } else {
            help();
            return -1;
        }
    } else if (argc == 3) {
        return 1;
    } else {
        help();
        return -1;
    }
    return BS;
}

int main(int argc, char *argv[]) {
    const int n = getSize(argc, argv);
    if (n == -1) {
        return -1;
    }

    const int BS = getBS(argc, argv);
    if (BS == -1) {
        return -1;
    }
    printf("size = %d\n", n);
    printf("BS = %d\n", BS);

    double *matrixA = malloc(sizeof(double) * n * n);
    if (!matrixA) {
        printf("Ошибка выделения памяти\n");
        exit(-1);
    }
    random_init(matrixA, n);
    // matrix_print(matrixA, n);

    double *matrixB = malloc(sizeof(double) * n * n);
    if (!matrixB) {
        printf("Ошибка выделения памяти\n");
        exit(-1);
    }
    random_init(matrixB, n);
    // matrix_print(matrixB, n);

    double *matrixC = malloc(sizeof(double) * n * n);
    if (!matrixC) {
        printf("Ошибка выделения памяти\n");
        exit(-1);
    }

    double t1, t2, t3;
    t1 = wtime();
    dgemm_def(matrixA, matrixB, matrixC, n);
    t1 = wtime() - t1;
    printf("Time dgemm_def = %lf\n", t1);
    // matrix_print(matrixC, n);
    zero_init(matrixC, n);
    t2 = wtime();
    dgemm_transpose(matrixA, matrixB, matrixC, n);
    t2 = wtime() - t2;
    printf("Time dgemm_transpose = %lf\n", t2);
    // matrix_print(matrixC, n);
    zero_init(matrixC, n);
    t3 = wtime();
    dgemm_block(matrixA, matrixB, matrixC, n, BS);
    t3 = wtime() - t3;
    printf("Time dgemm_block = %lf\n", t3);
    // matrix_print(matrixC, n);

    free(matrixA);
    free(matrixB);
    free(matrixC);

    FILE *File;

    File = fopen("./results/def.dat", "a");
    fprintf(File, "%d\t%lf\n", n, t1);
    fclose(File);
    File = fopen("./results/transpose.dat", "a");
    fprintf(File, "%d\t%lf\n", n, t2);
    fclose(File);
    File = fopen("./results/block.dat", "a");
    fprintf(File, "%d\t%lf\t%d\n", n, t3, BS);
    fclose(File);
    return 0;
}