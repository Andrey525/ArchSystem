#include "dgemm.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void random_init(double matrix[], const int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(matrix + i * n + j) = (double)(rand()) / RAND_MAX * 1000 + 1;
        }
    }
}
void zero_init(double matrix[], const int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(matrix + i * n + j) = 0;
        }
    }
}

void matrix_print(double matrix[], const int n) {
    printf("\nMatrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2lf ", *(matrix + i * n + j));
        }
        printf("\n");
    }
    printf("\n");
}

void dgemm_def(double matrixA[], double matrixB[], double matrixC[],
               const int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                *(matrixC + i * n + j) +=
                    *(matrixA + i * n + k) * *(matrixB + k * n + j);
            }
        }
    }
}

void dgemm_transpose(double matrixA[], double matrixB[], double matrixC[],
                     const int n) {
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                *(matrixC + i * n + j) +=
                    *(matrixA + i * n + k) * *(matrixB + k * n + j);
            }
        }
    }
}

void dgemm_block(double matrixA[], double matrixB[], double matrixC[],
                 const int n, const int BS) {
    int i, j, k, i0, j0, k0;
    double *a0, *b0, *c0;
    for (i = 0; i < n; i += BS) {
        for (j = 0; j < n; j += BS) {
            for (k = 0; k < n; k += BS) {
                for (i0 = 0, c0 = (matrixC + i * n + j),
                    a0 = (matrixA + i * n + k);
                     i0 < BS; ++i0, c0 += n, a0 += n) {
                    for (k0 = 0, b0 = (matrixB + k * n + j); k0 < BS;
                         ++k0, b0 += n) {
                        for (j0 = 0; j0 < BS; ++j0) {
                            c0[j0] += a0[k0] * b0[j0];
                        }
                    }
                }
            }
        }
    }
}