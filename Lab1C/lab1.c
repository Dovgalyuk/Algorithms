#include "array.h"
#include <stdbool.h>
#include <stdio.h>

Array *array_create_and_read(FILE *input) {
  int n;
  fscanf(input, "%d", &n);

  Array *arr = array_create(n, NULL);

  for (int i = 0; i < n; ++i) {
    int x;
    fscanf(input, "%d", &x);
    array_set(arr, i, x);
  }

  return arr;
}

Array *array_create_and_read_single_line(FILE *input) {
  int n;
  fscanf(input, "%d", &n);
  Array *arr = array_create(n, NULL);
  return arr;
}

void task1(Array *arr) {
  int remainder = 1;
  const int divisor = 17;

  for (size_t i = 0; i < array_size(arr); i++) {
    remainder *= 10;
    int digit = remainder / divisor;
    remainder %= divisor;
    array_set(arr, i, digit);
  }

  for (size_t i = 0; i < array_size(arr); i++) {
    printf("%d ", (int)array_get(arr, i));
  }
  printf("\n");
}

void task2(Array *arr) {
  size_t n = array_size(arr);

  for (size_t i = 0; i < n; i++) {
    int a = (int)array_get(arr, i);
    int is_divisible = false;

    for (size_t j = 0; j < n; j++) {
      if (i == j) {
        continue;
      }
      int b = (int)array_get(arr, j);

      if (b != 0 && a % b == 0) {
        is_divisible = true;
        break;
      }
    }

    if (!is_divisible) {
      printf("%d ", a);
    }
  }
  printf("\n");
}

int main(int argc, char **argv) {
  Array *arr = NULL;
  FILE *input = fopen(argv[1], "r");

  if (input == NULL) {
    printf("Error: Failed to open input file\n");
    return 1;
  }

  arr = array_create_and_read_single_line(input);
  task1(arr);
  array_delete(arr);

  arr = array_create_and_read(input);
  task2(arr);
  array_delete(arr);

  fclose(input);
}
