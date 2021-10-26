#pragma once

void matrix_print(double matrix[], const int n);

void random_init(double matrix[], const int n, const int CT);

void dgemm(double matrixA[], double matrixB[], double matrixC[], const int n,
           const int CT);