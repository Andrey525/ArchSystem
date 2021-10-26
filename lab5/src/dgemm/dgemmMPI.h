#pragma once

void random_init(double matrix[], const int n);

void zero_init(double matrix[], const int n);

void matrix_print(double matrix[], const int n);

void get_chunk(int a, int b, int commsize, int rank, int *lb, int *ub);