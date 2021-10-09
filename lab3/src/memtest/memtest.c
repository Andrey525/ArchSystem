#include "memtest.h"
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

double RAM_WT(int count_elements, int *array) {

    double t = wtime();
    for (int i = 0; i < count_elements; i++) {
        array[i] = i;
    }
    t = wtime() - t;
    return t;
}

double RAM_RT(int count_elements, int *array) {
    int k;
    double t = wtime();
    for (int i = 0; i < count_elements; i++) {
        k = array[i];
    }
    t = wtime() - t;
    return t;
}

double HDD_flash_WT(int block_size, char *path) {
    char *path_to_file = malloc(sizeof(char) * 255);
    path_to_file = strcpy(path_to_file, path);

    int count_elements = block_size / sizeof(int);
    block_size = sizeof(int) * count_elements;
    int *array = malloc(block_size);

    srand(time(NULL));
    for (int i = 0; i < count_elements; i++) {
        array[i] = rand() % 1000;
    }

    FILE *fp;
    path_to_file = strcat(path_to_file, "/test.txt");
    printf("path: %s\n", path_to_file);
    if ((fp = fopen(path_to_file, "w")) == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    double t = wtime();
    fwrite(array, sizeof(int), count_elements, fp);
    t = wtime() - t;
    fclose(fp);
    free(array);
    free(path_to_file);
    return t;
}

double HDD_flash_RT(int block_size, char *path) {
    char *path_to_file = malloc(sizeof(char) * 255);
    path_to_file = strcpy(path_to_file, path);

    int count_elements = block_size / sizeof(int);
    block_size = sizeof(int) * count_elements;
    int *array = malloc(block_size);

    FILE *fp;
    path_to_file = strcat(path_to_file, "/test.txt");
    if ((fp = fopen(path_to_file, "r")) == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    double t = wtime();
    if (fread(array, sizeof(int), count_elements, fp) != count_elements) {
        if (feof(fp)) {
            printf("Premature end of file.");
        } else {
            printf("File read error.");
            exit(1);
        }
    }
    t = wtime() - t;
    fclose(fp);
    free(array);
    free(path_to_file);
    return t;
}