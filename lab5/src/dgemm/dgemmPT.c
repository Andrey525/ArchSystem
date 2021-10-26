#include "dgemmPT.h"
#include <stdio.h>
#include <stdlib.h>

void random_init() {

    a = (double *)malloc(sizeof(double) * size * size);
    b = (double *)malloc(sizeof(double) * size * size);
    c = (double *)malloc(sizeof(double) * size * size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(a + i * size + j) = i + j + 1;
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(b + i * size + j) = i + j + 1;
        }
    }
}

void *dgemmPT(void *rank) {
    long my_rank = (long)rank;
    int i, j, k;
    int my_first_row = my_rank * local_size;
    int my_last_row = (my_rank + 1) * local_size - 1;

    for (i = my_first_row; i <= my_last_row; i++) {
        for (j = 0; j < size; j++) {
            for (k = 0; k < size; k++) {
                *(c + i * size + j) +=
                    *(a + i * size + k) * *(b + k * size + j);
            }
        }
    }
}

void matrix_print(double *matrix) {
    printf("\nMatrix:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%.2lf ", *(matrix + i * size + j));
        }
        printf("\n");
    }
    printf("\n");
}