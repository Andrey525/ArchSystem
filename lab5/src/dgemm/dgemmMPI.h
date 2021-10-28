#pragma once

void get_chunk(int a, int b, int commsize, int rank, int *lb, int *ub);

void random_init(double matrix[], const int n);

void dgemmMPI(double matrixA[], double matrixB[], double matrixC[],
              const int n);

void matrix_print(double matrix[], const int n);
