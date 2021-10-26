#pragma once

int thread_count;
int size, local_size;
double *a, *b, *c;

void random_init();
void *dgemmPT(void *rank);
void matrix_print(double *matrix);