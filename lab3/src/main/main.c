#include "memtest.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help() {
    printf(
        "Use, for example:\n./main -m RAM -b 1024 MB -l 10\n"
        "or:\n./main --memory-type RAM --block-size 1024 B --launch-count 10\n"
        "Supported memory types: RAM, HDD, flash\n"
        "Supported units: B, KB, MB\n");
}

typedef struct TestParameters {
    int block_size;
    int buffer_size;
    double tw;
    double tr;
    double abs_error_w;
    double rel_error_w;
    double abs_error_r;
    double rel_error_r;
    long int write_bandwidth;
    long int read_bandwidth;
} TestParameters;

void print_to_csv(int mem_type, TestParameters *param, double average_time_w,
                  double average_time_r, int launch_count) {
    FILE *fp = fopen("result.csv", "a");
    for (int i = 0; i < launch_count; i++) {
        char *string = malloc(sizeof(char) * 200);
        char *temp_string = malloc(sizeof(char) * 20);
        if (mem_type == 1) {
            strcpy(string, "RAM;");
        } else if (mem_type == 2) {
            strcpy(string, "HDD;");
        } else if (mem_type == 3) {
            strcpy(string, "flash;");
        }
        if (mem_type != 1) {
            sprintf(temp_string, "%d", param[i].block_size / 1024 / 1024);
            strcat(string, temp_string);
            strcat(string, ";int;");
            sprintf(temp_string, "%d", param[i].buffer_size / 1024 / 1024);
            strcat(string, temp_string);
            strcat(string, ";");
        } else {
            sprintf(temp_string, "%d", param[i].block_size);
            strcat(string, temp_string);
            strcat(string, ";int;");
            sprintf(temp_string, "%d", param[i].buffer_size);
            strcat(string, temp_string);
            strcat(string, ";");
        }
        sprintf(temp_string, "%d", i + 1);
        strcat(string, temp_string);
        strcat(string, ";gettimeofday;");
        sprintf(temp_string, "%lf", param[i].tw);
        strcat(string, temp_string);
        strcat(string, ";");
        sprintf(temp_string, "%lf", param[i].tr);
        strcat(string, temp_string);
        strcat(string, ";");
        sprintf(temp_string, "%lf", average_time_w);
        strcat(string, temp_string);
        strcat(string, ";");
        sprintf(temp_string, "%lf", average_time_r);
        strcat(string, temp_string);
        strcat(string, ";");
        sprintf(temp_string, "%ld", param[i].write_bandwidth / 1024 / 1024);
        strcat(string, temp_string);
        strcat(string, ";");
        if (mem_type != 1) {
            sprintf(temp_string, "%ld", param[i].read_bandwidth / 1024 / 1024);
            strcat(string, temp_string);
            strcat(string, ";");
        } else {
            strcat(string, "-;");
        }
        sprintf(temp_string, "%lf", param[i].abs_error_w);
        strcat(string, temp_string);
        strcat(string, ";");
        sprintf(temp_string, "%lf", param[i].rel_error_w);
        strcat(string, temp_string);
        strcat(string, ";");
        sprintf(temp_string, "%lf", param[i].abs_error_r);
        strcat(string, temp_string);
        strcat(string, ";");
        sprintf(temp_string, "%lf", param[i].rel_error_r);
        strcat(string, temp_string);
        strcat(string, ";");
        fprintf(fp, "%s\n", string);
        free(string);
        free(temp_string);
    }
    fclose(fp);
}

int main(int argc, char *argv[]) {
    int mem_type = 0;
    int block_size = 0;
    int launch_count = 0;

    if (argc == 8) {

        if (((strcmp(argv[1], "-m") == 0) ||
             (strcmp(argv[1], "--memory-type") == 0)) &&
            ((strcmp(argv[3], "-b") == 0) ||
             (strcmp(argv[3], "--block-size") == 0)) &&
            ((strcmp(argv[6], "-l") == 0) ||
             (strcmp(argv[6], "--launch-count") == 0))) {

            if (strcmp(argv[2], "RAM") == 0) {
                mem_type = 1;
            } else if (strcmp(argv[2], "HDD") == 0) {
                mem_type = 2;
            } else if (strcmp(argv[2], "flash") == 0) {
                mem_type = 3;
            } else {
                help();
                return 1;
            }

            int num_count = 0;
            for (int i = 0; i < strlen(argv[4]); i++) {
                if (argv[4][i] >= '0' && argv[4][i] <= '9') {
                    num_count++;
                }
            }
            if (num_count == strlen(argv[4])) {
                block_size = atoi(argv[4]);
            } else {
                help();
                return 1;
            }

            if (strcmp(argv[5], "KB") == 0) {
                block_size *= 1024;
            } else if (strcmp(argv[5], "MB") == 0) {
                block_size *= (1024 * 1024);
            } else if (strcmp(argv[5], "B") != 0) {
                help();
                return 1;
            }

            num_count = 0;
            for (int i = 0; i < strlen(argv[7]); i++) {
                if (argv[7][i] >= '0' && argv[7][i] <= '9') {
                    num_count++;
                }
            }
            if (num_count == strlen(argv[7])) {
                launch_count = atoi(argv[7]);
            } else {
                help();
                return 1;
            }

        } else {
            help();
            return 1;
        }
    } else {
        help();
        return 1;
    }

    printf("Mem type = %d, block size = %d, launch count = %d\n", mem_type,
           block_size, launch_count);
    TestParameters param[launch_count];
    double sum_time_w = 0;
    double sum_time_r = 0;
    double average_time_w;
    double average_time_r;
    int write_bandwidth;
    int read_bandwidth;
    switch (mem_type) {
    case 1:
        param[0].block_size = 64;
        param[1].block_size = 32 * 1024;
        param[2].block_size = 2048 * 1024;
        for (int i = 3; i < launch_count; i++) {
            param[i].block_size = param[i - 1].block_size + 1024 * 1024;
        }
        for (int i = 0; i < launch_count; i++) {
            printf("block size = %d\n", param[i].block_size);
            int count_elements = param[i].block_size / sizeof(int);
            int *array = malloc(param[i].block_size);
            printf("Num launch = %d\n", i + 1);
            param[i].tw = RAM_WT(count_elements, array);
            printf("t(write) = %lf\n", param[i].tw);
            param[i].tr = RAM_RT(count_elements, array);
            printf("t(read) = %lf\n", param[i].tr);
            free(array);
            printf("_____________\n");
            param[i].buffer_size = 4;
            sum_time_w = sum_time_w + param[i].tw;
            sum_time_r = sum_time_r + param[i].tr;
        }
        average_time_w = sum_time_w / launch_count;
        average_time_r = sum_time_r / launch_count;

        for (int i = 0; i < launch_count; i++) {
            param[i].abs_error_w = fabs(param[i].tw - average_time_w);
            param[i].abs_error_r = fabs(param[i].tr - average_time_r);
            param[i].rel_error_w = param[i].abs_error_w / param[i].tw;
            param[i].rel_error_r = param[i].abs_error_r / param[i].tr;
            param[i].write_bandwidth = param[i].block_size / param[i].tw;
            param[i].read_bandwidth = param[i].block_size / param[i].tr;
        }
        print_to_csv(mem_type, param, average_time_w, average_time_r,
                     launch_count);
        break;
    case 2:
        for (int i = 0; i < launch_count; i++, block_size += 4 * 1024 * 1024) {
            printf("Num launch = %d\n", i + 1);
            param[i].tw = HDD_flash_WT(block_size, ".");
            printf("t(write) = %lf\n", param[i].tw);
            param[i].tr = HDD_flash_RT(block_size, ".");
            printf("t(read) = %lf\n", param[i].tr);
            printf("_____________\n");
            param[i].block_size = block_size;
            param[i].buffer_size = block_size;
            sum_time_w = sum_time_w + param[i].tw;
            sum_time_r = sum_time_r + param[i].tr;
        }

        average_time_w = sum_time_w / launch_count;
        average_time_r = sum_time_r / launch_count;
        for (int i = 0; i < launch_count; i++) {
            param[i].abs_error_w = fabs(param[i].tw - average_time_w);
            param[i].abs_error_r = fabs(param[i].tr - average_time_r);
            param[i].rel_error_w = param[i].abs_error_w / param[i].tw;
            param[i].rel_error_r = param[i].abs_error_r / param[i].tr;
            param[i].write_bandwidth = param[i].block_size / param[i].tw;
            param[i].read_bandwidth = param[i].block_size / param[i].tr;
        }
        print_to_csv(mem_type, param, average_time_w, average_time_r,
                     launch_count);
        break;
    case 3:
        for (int i = 0; i < launch_count; i++, block_size += 4 * 1024 * 1024) {
            printf("Num launch = %d\n", i + 1);
            param[i].tw = HDD_flash_WT(block_size, "/media/andrey/SMARTBUY8GB");
            printf("t(write) = %lf\n", param[i].tw);
            param[i].tr = HDD_flash_RT(block_size, "/media/andrey/SMARTBUY8GB");
            printf("t(read) = %lf\n", param[i].tr);
            printf("_____________\n");
            param[i].block_size = block_size;
            param[i].buffer_size = block_size;
            sum_time_w = sum_time_w + param[i].tw;
            sum_time_r = sum_time_r + param[i].tr;
        }
        average_time_w = sum_time_w / launch_count;
        average_time_r = sum_time_r / launch_count;
        for (int i = 0; i < launch_count; i++) {
            param[i].abs_error_w = fabs(param[i].tw - average_time_w);
            param[i].abs_error_r = fabs(param[i].tr - average_time_r);
            param[i].rel_error_w = param[i].abs_error_w / param[i].tw;
            param[i].rel_error_r = param[i].abs_error_r / param[i].tr;
            param[i].write_bandwidth = param[i].block_size / param[i].tw;
            param[i].read_bandwidth = param[i].block_size / param[i].tr;
        }
        print_to_csv(mem_type, param, average_time_w, average_time_r,
                     launch_count);
        break;
    }
    return 0;
}