#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define N 1000

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

double run_double() {
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

    return t;
}

double run_float() {
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

    return t;
}

double run_int() {
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

    return t;
}

char *getLine(char *filename, int needed) {
    char *line = malloc(sizeof(char) * 250);
    FILE *f = fopen(filename, "r");
    int c = 0;
    while (c < needed && !feof(f)) {
        line = fgets(line, 50, f);
        c++;
    }
    fclose(f);
    if (c != needed) {
        return NULL;
    }
    return strdup(line); // не забыть потом освободить буфер
}

typedef struct TestParameters {
    int instruction_count;
    double time;
    int l_num;
    double abs_error;
    double rel_error;
    double task_perf;
} TestParameters;

int main(int argc, char *argv[]) {
    int count_of_tests;
    int data_type;
    const char task[] = "dgemv";

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

    printf("Task name = %s\n", task);
    printf("count_of_tests = %d\n", count_of_tests);
    printf("data_type = %d\n", data_type);

    TestParameters *tp = malloc(sizeof(TestParameters) * count_of_tests);

    char *opt = malloc(sizeof(char) * 5);
    opt = strcpy(opt, "-O");
    char *temp_opt = getLine("info.txt", 2);
    strcat(opt, temp_opt);
    opt[strlen(opt) - 1] = '\0';
    printf("opt = %s\n", opt);

    char *pmodel = malloc(sizeof(char) * 50);
    pmodel = getLine("info.txt", 1);
    printf("PModel = %s", pmodel);
    pmodel[strlen(pmodel) - 1] = '\0';

    switch (data_type) {
    case 0:
        for (int i = 0; i < count_of_tests; i++) {
            tp[i].l_num = i + 1;
            printf("lnum = %d\n", tp[i].l_num);
            tp[i].time = run_double();
        }
        break;
    case 1:
        for (int i = 0; i < count_of_tests; i++) {
            tp[i].l_num = i + 1;
            printf("lnum = %d\n", tp[i].l_num);
            tp[i].time = run_float();
        }
        break;
    case 2:
        for (int i = 0; i < count_of_tests; i++) {
            tp[i].l_num = i + 1;
            printf("lnum = %d\n", tp[i].l_num);
            tp[i].time = run_int();
            printf("time = %lf\n", tp[i].time);
        }
        break;
    }
    double middle_time = 0;
    double sum_time = 0;
    for (int i = 0; i < count_of_tests; i++) {
        sum_time = sum_time + tp[i].time;
    }
    middle_time = sum_time / count_of_tests;
    printf("middle_time = %lf\n", middle_time);

    for (int i = 0; i < count_of_tests; i++) {
        tp[i].abs_error = fabs(tp[i].time - middle_time);
        printf("abs_error = %lf\n", tp[i].abs_error);
        tp[i].rel_error = (tp[i].abs_error / tp[i].time) * 100;
        printf("rel_error = %lf%%\n", tp[i].rel_error);
    }

    char *string[count_of_tests];
    char *num_in_string = malloc(sizeof(char) * 20);

    FILE *fp = fopen("result.csv", "a");
    for (int i = 0; i < count_of_tests; i++) {
        string[i] = malloc(sizeof(char) * 200);
        strcpy(string[i], pmodel);
        strcat(string[i], ";");
        strcat(string[i], task);
        strcat(string[i], ";");
        switch (data_type) {
        case 0:
            strcat(string[i], "double;");
            break;
        case 1:
            strcat(string[i], "float;");
            break;
        case 2:
            strcat(string[i], "int;");
            break;
        }
        strcat(string[i], opt);
        strcat(string[i], ";");

        strcat(string[i], "gettimeofday");
        strcat(string[i], ";");

        sprintf(num_in_string, "%lf", tp[i].time);
        strcat(string[i], num_in_string);
        strcat(string[i], ";");

        sprintf(num_in_string, "%d", tp[i].l_num);
        strcat(string[i], num_in_string);
        strcat(string[i], ";");

        sprintf(num_in_string, "%lf", middle_time);
        strcat(string[i], num_in_string);
        strcat(string[i], ";");

        sprintf(num_in_string, "%lf", tp[i].abs_error);
        strcat(string[i], num_in_string);
        strcat(string[i], ";");
        sprintf(num_in_string, "%lf", tp[i].rel_error);
        strcat(string[i], num_in_string);
        strcat(string[i], ";");
        printf("%s\n", string[i]);
        if (i == count_of_tests - 1) {
            fprintf(fp, "%s", string[i]);
        } else {
            fprintf(fp, "%s\n", string[i]);
        }
    }

    return 0;
}
