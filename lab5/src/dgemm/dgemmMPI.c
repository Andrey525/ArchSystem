#include "dgemmMPI.h"
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void random_init(double matrix[], const int n) {
    int commsize, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    for (int i = rank; i < n; i += commsize) {
        for (int j = 0; j < n; j++) {
            *(matrix + i * n + j) = (double)(rand()) / RAND_MAX * 10 + 1;
        }
    }
}
