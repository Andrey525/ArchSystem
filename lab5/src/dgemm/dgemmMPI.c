#include "dgemmMPI.h"
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void get_chunk(int a, int b, int commsize, int rank, int *lb, int *ub) {
    int n = b - a + 1;
    int q = n / commsize;
    if (n % commsize) {
        q++;
    }
    int r = commsize * q - n;
    int chunk = q;
    // первым commsize - r процессам достанется на одну строку больше
    if (rank >= commsize - r) {
        chunk = q - 1;
    }
    *lb = a;
    if (rank > 0) {
        if (rank <= commsize - r) {
            *lb += q * rank;
        } else {
            *lb = q * (commsize - r) + (q - 1) * (rank - (commsize - r));
        }
    }
    *ub = *lb + chunk - 1;
}

void random_init(double matrix[], const int n) {
    int commsize, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    srand(rank);

    int lb, ub;
    get_chunk(0, n - 1, commsize, rank, &lb, &ub);
    int rows_count = ub - lb + 1;

    for (int i = 0; i < rows_count; i++) {
        for (int j = 0; j < n; j++) {
            *(matrix + lb + i * n + j) = (double)(rand()) / RAND_MAX * 10 + 1;
        }
    }

    int *displs = malloc(sizeof(int) * commsize);
    int *rcounts = malloc(sizeof(int) * commsize);
    for (int i = 0; i < commsize; i++) {
        get_chunk(0, n - 1, commsize, i, &lb, &ub);
        rows_count = ub - lb + 1;
        rcounts[i] = rows_count;
        displs[i] = (i > 0) ? displs[i - 1] + rcounts[i - 1] : 0;
    }
    MPI_Allgatherv(MPI_IN_PLACE, 0, MPI_FLOAT, matrix, rcounts, displs,
                   MPI_FLOAT, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
}

void matrix_print(double matrix[], const int n) {
    int rank, commsize;
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%.2lf ", *(matrix + i * n + j));
            }
            printf("\n");
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
}