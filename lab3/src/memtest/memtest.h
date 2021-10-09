#pragma once
double HDD_flash_WT(int block_size, char *path);
double HDD_flash_RT(int block_size, char *path);
double RAM_WT(int count_elements, int *array);
double RAM_RT(int count_elements, int *array);