#include "../LibraryC/array.h"
#include <time.h>

Array *array_create_and_read(FILE *input) {
  int n;
  fscanf(input, "%d", &n);
  /* Create array */
  Array *arr = array_create(n, NULL);
  /* Read array data */
  for (int i = 0; i < n; ++i) {
    int x;
    fscanf(input, "%d", &x);
    array_set(arr, i, x);
  }
  return arr;
}

void task1(Array *arr) {
  srand(time(NULL));

  int n = array_size(arr);
  int sum = 0;

  for (int i = 0; i < n; i++) {
    int random_height = rand() % 51 + 150;
    array_set(arr, i, random_height);
    sum += random_height;
  }

  double average = (double)sum / n;

  int count = 0;
  for (int i = 0; i < n; i++) {
    int height = array_get(arr, i);
    ;
    if (height > average) {
      count++;
    }
  }
  printf("Средний рост: %.2f\n", average);
  printf("Количество учеников выше среднего роста: %d\n", count);
}

void task2(Array *arr) {}

int main(int argc, char **argv) {
  Array *arr = NULL;
  FILE *input = fopen(argv[1], "r");
  arr = array_create_and_read(input);
  task1(arr);
  array_delete(arr);
  /* Create another array here */
  arr = array_create_and_read(input);
  task2(arr);
  array_delete(arr);
  fclose(input);
}
