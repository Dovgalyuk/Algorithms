#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция для чтения массива из файла
Array *array_create_and_read(FILE *input) {
  int n;
  if (fscanf(input, "%d", &n) != 1) {
    printf("Ошибка чтения размера массива.\n");
    return NULL;
  }
  printf("Размер массива: %d\n", n);

  Array *arr = array_create(n, NULL);
  if (!arr) {
    printf("Ошибка создания массива.\n");
    return NULL;
  }

  for (int i = 0; i < n; ++i) {
    int x;
    if (fscanf(input, "%d", &x) != 1) {
      printf("Ошибка чтения элемента массива.\n");
      array_delete(arr);
      return NULL;
    }
    array_set(arr, i, (Data)(intptr_t)x);

  }
  return arr;
}

void read_range(FILE *input, int *a, int *b) {
  if (fscanf(input, "%d %d", a, b) != 2) {
    printf("Ошибка чтения границ диапазона.\n");
  } else {
    printf("Диапазон: [%d, %d]\n", *a, *b);
  }
}

void task1(Array *arr) {
  srand(time(NULL));

  int n = array_size(arr);
  int sum = 0;

  for (int i = 0; i < n; i++) {
    int random_height = rand() % 51 + 150;
    array_set(arr, i, (Data)(intptr_t)random_height);
    sum += random_height;
  }

  double average = (double)sum / n;
  int count = 0;
  for (int i = 0; i < n; i++) {
    int height = (int)(intptr_t)array_get(arr, i);
    if (height > average) {
      count++;
    }
  }
  printf("Средний рост: %.2f\n", average);
  printf("Количество учеников выше среднего роста: %d\n", count);
}

void task2(Array *arr, int a, int b) {
  srand(time(NULL));

  int n = array_size(arr);
  int valid_elements = 0;

  for (int i = 0; i < n; i++) {
    int random_number = rand() % 100 + 1;
    array_set(arr, i, (Data)(intptr_t)random_number);
  }

  printf("Массив перед сжатием: ");
  for (int i = 0; i < n; i++) {
    int value = (int)(intptr_t)array_get(arr, i);
    printf("%d ", value);
  }
  printf("\n");

  for (int i = 0; i < n; i++) {
    int value = (int)(intptr_t)array_get(arr, i);
    if (value < a || value > b) {
      array_set(arr, valid_elements, (Data)(intptr_t)value);
      valid_elements++;
    }
  }

  for (int i = valid_elements; i < n; i++) {
    array_set(arr, i, (Data)(intptr_t)0);
  }

  printf("Массив после сжатия: ");
  for (int i = 0; i < n; i++) {
    int value = (int)(intptr_t)array_get(arr, i);
    printf("%d ", value);
  }
  printf("\n");
}


int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Ошибка: Укажите файл для ввода данных.\n");
    return 1;
  }

  FILE *input = fopen(argv[1], "r");
  if (!input) {
    printf("Ошибка: Не удалось открыть файл.\n");
    return 1;
  }

  Array *arr = array_create_and_read(input);
  if (!arr) {
    fclose(input);
    return 1;
  }
  task1(arr);
  array_delete(arr);

  int n;
  if (fscanf(input, "%d", &n) != 1) {
    printf("Ошибка чтения размера массива для второго задания.\n");
    fclose(input);
    return 1;
  }

  arr = array_create(n, NULL);
  if (!arr) {
    fclose(input);
    return 1;
  }

  int a, b;
  read_range(input, &a, &b);

  task2(arr, a, b);
  array_delete(arr);

  fclose(input);
  return 0;
}
