#include "dgemmOMP.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void random_init(double matrix[], const int n, const int CT) {
#pragma omp parallel num_threads(CT)
    {
        int nthreads = omp_get_num_threads();
        int threadid = omp_get_thread_num();
        int items_per_thread = n / nthreads;
        int lb = threadid * items_per_thread;
        int ub =
            (threadid == nthreads - 1) ? (n - 1) : (lb + items_per_thread - 1);

        for (int i = lb; i <= ub; i++) {
            for (int j = 0; j < n; j++) {
                *(matrix + i * n + j) = (double)(rand()) / RAND_MAX * 10 + 1;
            }
        }
    }
}

void dgemm(double matrixA[], double matrixB[], double matrixC[], const int n,
           const int CT) {
#pragma omp parallel num_threads(CT)
    {
        int nthreads = omp_get_num_threads();
        int threadid = omp_get_thread_num();
        int items_per_thread = n / nthreads;
        int lb = threadid * items_per_thread;
        int ub =
            (threadid == nthreads - 1) ? (n - 1) : (lb + items_per_thread - 1);

        for (int i = lb; i <= ub; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    *(matrixC + i * n + j) +=
                        *(matrixA + i * n + k) * *(matrixB + k * n + j);
                }
            }
        }
    }
}