#include "memtest.h"
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

void print_to_csv(int mem_type, int block_size, int buffer_size, int launch_num,
                  double tw, double tr, int launch_count) {
    FILE *fp = fopen("result.csv", "a");
    char *string = malloc(sizeof(char) * 200);
    char *temp_string = malloc(sizeof(char) * 20);
    if (mem_type == 1) {
        strcpy(string, "RAM;");
    } else if (mem_type == 2) {
        strcpy(string, "HDD;");
    } else if (mem_type == 3) {
        strcpy(string, "flash;");
    }
    sprintf(temp_string, "%d", block_size / 1024 / 1024);
    strcat(string, temp_string);
    strcat(string, ";int;");
    sprintf(temp_string, "%d", buffer_size / 1024 / 1024);
    strcat(string, temp_string);
    strcat(string, ";");
    sprintf(temp_string, "%d", launch_num);
    strcat(string, temp_string);
    strcat(string, ";gettimeofday;");
    sprintf(temp_string, "%lf", tw);
    strcat(string, temp_string);
    strcat(string, ";");
    sprintf(temp_string, "%lf", tr);
    strcat(string, temp_string);
    strcat(string, ";");
    if (launch_count != launch_num) {
        fprintf(fp, "%s\n", string);
    } else {
        fprintf(fp, "%s", string);
    }
    free(string);
    free(temp_string);
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

    double tw, tr;
    int arsi[launch_count];
    switch (mem_type) {
    case 1:
        arsi[0] = 64;
        arsi[1] = 32 * 1024;
        arsi[2] = 2048 * 1024;
        for (int i = 3; i < launch_count; i++) {
            arsi[i] = arsi[i - 1] + 1024 * 1024;
        }
        block_size = arsi[0];
        for (int i = 0; i < launch_count; i++, block_size = arsi[i]) {
            printf("block size = %d\n", block_size);
            int count_elements = block_size / sizeof(int);
            block_size = sizeof(int) * count_elements;
            int *array = malloc(block_size);
            printf("Num launch = %d\n", i + 1);
            tw = RAM_WT(count_elements, array);
            printf("t(write) = %lf\n", tw);
            tr = RAM_RT(count_elements, array);
            printf("t(read) = %lf\n", tr);
            free(array);
            printf("_____________\n");
            print_to_csv(mem_type, block_size, 1, i + 1, tw, tr, launch_count);
        }
        break;
    case 2:
        for (int i = 0; i < launch_count; i++, block_size += 4 * 1024 * 1024) {
            printf("Num launch = %d\n", i + 1);
            tw = HDD_flash_WT(block_size, ".");
            printf("t(write) = %lf\n", tw);
            tr = HDD_flash_RT(block_size, ".");
            printf("t(read) = %lf\n", tr);
            printf("_____________\n");
            print_to_csv(mem_type, block_size, block_size, i + 1, tw, tr,
                         launch_count);
        }
        break;
    case 3:
        for (int i = 0; i < launch_count; i++, block_size += 4 * 1024 * 1024) {
            printf("Num launch = %d\n", i + 1);
            tw = HDD_flash_WT(block_size, "/media/andrey/SMARTBUY8GB");
            printf("t(write) = %lf\n", tw);
            tr = HDD_flash_RT(block_size, "/media/andrey/SMARTBUY8GB");
            printf("t(read) = %lf\n", tr);
            printf("_____________\n");
            print_to_csv(mem_type, block_size, block_size, i + 1, tw, tr,
                         launch_count);
        }
        break;
    }
    return 0;
}