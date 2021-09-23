#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void matrix_vector_product(double *a, double *b, double *c, int m, int n) {
    for (int i = 0; i < m; i++) {
        c[i] = 0.0;
        for (int j = 0; j < n; j++)
            c[i] += a[i * n + j] * b[j];
    }
}

void print_all(double *a, double *b, double *c, int m, int n) {
    printf("\nMatrix A:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5.0lf ", a[i * n + j]);
        }
        printf("\n");
    }
    printf("\nVector B:\n");
    for (int j = 0; j < n; j++) {
        printf("%5.0lf ", b[j]);
    }
    printf("\n");
    printf("\nVector С:\n");
    for (int i = 0; i < m; i++) {
        printf("%5.0lf\n", c[i]);
    }
    printf("\n");
}

void run(int m, int n) {
    double *a, *b, *c;
    a = malloc(sizeof(*a) * m * n);
    if (!a) {
        printf("Ошибка выделения памяти под матрицу A\n");
        exit(-1);
    }
    b = malloc(sizeof(*b) * n);
    if (!b) {
        printf("Ошибка выделения памяти под вектор B\n");
        exit(-1);
    }
    c = malloc(sizeof(*c) * m);
    if (!c) {
        printf("Ошибка выделения памяти под вектор C\n");
        exit(-1);
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            a[i * n + j] = i + j;
        }
    }
    for (int j = 0; j < n; j++) {
        b[j] = j;
    }

    print_all(a, b, c, m, n);

    double t = wtime();
    matrix_vector_product(a, b, c, m, n);
    t = wtime() - t;
    printf("Elapsed time (serial): %.6f sec.\n", t);

    print_all(a, b, c, m, n);
    free(a);
    free(b);
    free(c);
}

int main(int argc, char *argv[]) {
    int count_of_tests;
    if (argc == 3) {
        if (strcmp(argv[1], "counttests") == 0) {
            count_of_tests = atoi(argv[2]);
        }
    } else if (argc == 1) {
        count_of_tests = 10;
    } else {
        printf("Возможные варианты:\n./prog\n./prog counttests {число тестов} "
               "(Пример: ./prog counttests 20)\n");
        exit(1);
    }
    printf("count_of_tests = %d\n", count_of_tests);

    int m = 10;
    int n = 10;
    run(m, n);
    return 0;
}
