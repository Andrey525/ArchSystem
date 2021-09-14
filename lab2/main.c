#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int count_of_tests = 10;
  if (argc == 3) {
    if (strcmp(argv[1], "counttests") == 0) {
      count_of_tests = atoi(argv[2]);
    }
  }
  printf("count_of_tests = %d\n", count_of_tests);
  return 0;
}
