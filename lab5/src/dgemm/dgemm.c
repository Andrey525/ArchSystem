#include "dgemm.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void random_init(double matrix[], const int n) {
    // srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(matrix + i * n + j) = (double)(rand()) / RAND_MAX * 10 + 1;
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
