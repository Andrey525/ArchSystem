#include "dgemm.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}
