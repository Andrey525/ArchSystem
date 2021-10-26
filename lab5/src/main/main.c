#include "../dgemm/dgemm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

void help() {
    printf("Incorrect input of arguments!\n"
           "Use, for example: ./dgemmexe --size 2048\n");
}

double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
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
    double t_init, t_dgemm;
    const int n = getSize(argc, argv);
    if (n == -1) {
        return -1;
    }
    printf("size = %d\n", n);

    t_init = wtime();
    double *matrixA = malloc(sizeof(double) * n * n);
    if (!matrixA) {
        printf("Ошибка выделения памяти\n");
        exit(-1);
    }
    random_init(matrixA, n);
    double *matrixB = malloc(sizeof(double) * n * n);
    if (!matrixB) {
        printf("Ошибка выделения памяти\n");
        exit(-1);
    }
    random_init(matrixB, n);
    double *matrixC = malloc(sizeof(double) * n * n);
    if (!matrixC) {
        printf("Ошибка выделения памяти\n");
        exit(-1);
    }
    t_init = wtime() - t_init;

    t_dgemm = wtime();
    dgemm_def(matrixA, matrixB, matrixC, n);
    t_dgemm = wtime() - t_dgemm;
    printf("t_init = %.6lf \t t_dgemm = %.6lf\n", t_init, t_dgemm);

    free(matrixA);
    free(matrixB);
    free(matrixC);

    FILE *File;
    File = fopen("./results/sinle.dat", "a");
    fprintf(File, "%d\t%lf\t%lf\n", n, t_init, t_dgemm);
    fclose(File);
    return 0;
}