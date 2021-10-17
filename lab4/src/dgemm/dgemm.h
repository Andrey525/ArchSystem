#pragma once

void random_init(double matrix[], const int n);

void zero_init(double matrix[], const int n);

void matrix_print(double matrix[], const int n);

void dgemm_def(double matrixA[], double matrixB[], double matrixC[],
               const int n);

void dgemm_transpose(double matrixA[], double matrixB[], double matrixC[],
                     const int n);

void dgemm_block(double matrixA[], double matrixB[], double matrixC[],
                 const int n, const int BS);
