#include "../dgemm/dgemmMPI.h"
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>

void help() {
    printf("Incorrect input of arguments!\n"
           "Use, for example: ./dgemmMPIexe --size 2048\n");
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
    int rank, commsize;
    const int n = getSize(argc, argv);
    if (n == -1) {
        return -1;
    }
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double t_init, t_dgemm;

    t_init = MPI_Wtime();
    double *matrixA = calloc(n * n, sizeof(double));
    if (!matrixA) {
        printf("Ошибка выделения памяти\n");
        exit(-1);
    }
    random_init(matrixA, n);
    double *matrixB = calloc(n * n, sizeof(double));
    if (!matrixB) {
        printf("Ошибка выделения памяти\n");
        exit(-1);
    }
    random_init(matrixB, n);
    double *matrixC = calloc(n * n, sizeof(double));
    if (!matrixC) {
        printf("Ошибка выделения памяти\n");
        exit(-1);
    }
    t_init = MPI_Wtime() - t_init;

    t_dgemm = MPI_Wtime();
    dgemmMPI(matrixA, matrixB, matrixC, n);
    t_dgemm = MPI_Wtime() - t_dgemm;

    if (rank == 0) {
        FILE *File;
        File = fopen("./results/MPI.dat", "a");
        fseek(File, 0, SEEK_END);
        long pos = ftell(File);
        if (pos == 0) {
            fprintf(File, "%s%s\t%s\t%s\t%s\n", "#", "size", "commsize",
                    "t_init", "t_dgemm");
            fprintf(File, "%d\t%d\t%lf\t%lf\n", n, commsize, t_init, t_dgemm);
        } else {
            fprintf(File, "%d\t%d\t%lf\t%lf\n", n, commsize, t_init, t_dgemm);
        }
        fclose(File);
    }

    free(matrixA);
    free(matrixB);
    free(matrixC);

    MPI_Finalize();
    return 0;
}