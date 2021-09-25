#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define N 10000

double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void dgemv_double(double *a, double *b, double *c) {
    for (int i = 0; i < N; i++) {
        c[i] = 0.0;
        for (int j = 0; j < N; j++)
            c[i] += a[i * N + j] * b[j];
    }
}

void dgemv_float(float *a, float *b, float *c) {
    for (int i = 0; i < N; i++) {
        c[i] = 0.0;
        for (int j = 0; j < N; j++)
            c[i] += a[i * N + j] * b[j];
    }
}

void dgemv_int(int *a, int *b, int *c) {
    for (int i = 0; i < N; i++) {
        c[i] = 0;
        for (int j = 0; j < N; j++)
            c[i] += a[i * N + j] * b[j];
    }
}

void print_all(double *a, double *b, double *c) {
    printf("\nMatrix A:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%5.0lf ", a[i * N + j]);
        }
        printf("\n");
    }
    printf("\nVector B:\n");
    for (int j = 0; j < N; j++) {
        printf("%5.0lf ", b[j]);
    }
    printf("\n");
    printf("\nVector С:\n");
    for (int i = 0; i < N; i++) {
        printf("%5.0lf\n", c[i]);
    }
    printf("\n");
}

void run_double() {
    double *a, *b, *c;
    a = malloc(sizeof(*a) * N * N);
    if (!a) {
        printf("Ошибка выделения памяти под матрицу A\n");
        exit(-1);
    }
    b = malloc(sizeof(*b) * N);
    if (!b) {
        printf("Ошибка выделения памяти под вектор B\n");
        exit(-1);
    }
    c = malloc(sizeof(*c) * N);
    if (!c) {
        printf("Ошибка выделения памяти под вектор C\n");
        exit(-1);
    }

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i * N + j] = rand() % 10 + 1;
        }
    }
    for (int j = 0; j < N; j++) {
        b[j] = rand() % 10 + 1;
    }

    double t = wtime();
    dgemv_double(a, b, c);
    t = wtime() - t;
    printf("Elapsed time (double): %.6f sec.\n", t);

    free(a);
    free(b);
    free(c);
}

void run_float() {
    float *a, *b, *c;
    a = malloc(sizeof(*a) * N * N);
    if (!a) {
        printf("Ошибка выделения памяти под матрицу A\n");
        exit(-1);
    }
    b = malloc(sizeof(*b) * N);
    if (!b) {
        printf("Ошибка выделения памяти под вектор B\n");
        exit(-1);
    }
    c = malloc(sizeof(*c) * N);
    if (!c) {
        printf("Ошибка выделения памяти под вектор C\n");
        exit(-1);
    }

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i * N + j] = rand() % 10 + 1;
        }
    }
    for (int j = 0; j < N; j++) {
        b[j] = rand() % 10 + 1;
    }

    double t = wtime();
    dgemv_float(a, b, c);
    t = wtime() - t;
    printf("Elapsed time (float): %.6f sec.\n", t);

    free(a);
    free(b);
    free(c);
}

void run_int() {
    int *a, *b, *c;
    a = malloc(sizeof(*a) * N * N);
    if (!a) {
        printf("Ошибка выделения памяти под матрицу A\n");
        exit(-1);
    }
    b = malloc(sizeof(*b) * N);
    if (!b) {
        printf("Ошибка выделения памяти под вектор B\n");
        exit(-1);
    }
    c = malloc(sizeof(*c) * N);
    if (!c) {
        printf("Ошибка выделения памяти под вектор C\n");
        exit(-1);
    }

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i * N + j] = rand() % 10 + 1;
        }
    }
    for (int j = 0; j < N; j++) {
        b[j] = rand() % 10 + 1;
    }

    double t = wtime();
    dgemv_int(a, b, c);
    t = wtime() - t;
    printf("Elapsed time (int): %.6f sec.\n", t);

    free(a);
    free(b);
    free(c);
}

int main(int argc, char *argv[]) {
    int count_of_tests;
    int data_type;

    /*** Возимся с аргументами командной строки***/
    if (argc == 4) {
        if (strcmp(argv[1], "-counttests") == 0) {
            int num_count = 0;
            for (int i = 0; i < strlen(argv[2]); i++) {
                if (argv[2][i] >= '0' && argv[2][i] <= '9') {
                    num_count++;
                }
            }
            if (num_count == strlen(argv[2])) {
                count_of_tests = atoi(argv[2]);
            } else {
                printf(
                    "Возможные варианты:\n./bin/prog\n./bin/prog -counttests "
                    "{число "
                    "тестов} -{тип данных}"
                    "(Пример: ./bin/prog -counttests 20 -float)\n");
                exit(1);
            }
        } else {
            printf("Возможные варианты:\n./bin/prog\n./bin/prog -counttests "
                   "{число "
                   "тестов} -{тип данных}"
                   "(Пример: ./bin/prog -counttests 20 -float)\n");
            exit(1);
        }
        if (strcmp(argv[3], "-double") == 0) {
            data_type = 0;
        } else if (strcmp(argv[3], "-float") == 0) {
            data_type = 1;
        } else if (strcmp(argv[3], "-int") == 0) {
            data_type = 2;
        } else {
            printf("Возможные варианты:\n./bin/prog\n./bin/prog -counttests "
                   "{число "
                   "тестов} -{тип данных}"
                   "(Пример: ./bin/prog -counttests 20 -float)\n");
            exit(1);
        }
    } else if (argc == 1) {
        count_of_tests = 10;
        data_type = 0;
    } else {
        printf("Возможные варианты:\n./bin/prog\n./bin/prog -counttests {число "
               "тестов} -{тип данных}"
               "(Пример: ./bin/prog -counttests 20 -float)\n");
        exit(1);
    }
    /*** Конец***/

    printf("count_of_tests = %d\n", count_of_tests);
    printf("data_type = %d\n", data_type);

    switch (data_type) {
    case 0:
        for (int i = 0; i < count_of_tests; i++) {
            printf("Test number %d\n", i + 1);
            run_double();
        }
        break;
    case 1:
        for (int i = 0; i < count_of_tests; i++) {
            printf("Test number %d\n", i + 1);
            run_float();
        }
        break;
    case 2:
        for (int i = 0; i < count_of_tests; i++) {
            printf("Test number %d\n", i + 1);
            run_int();
        }
        break;
    }
    return 0;
}
