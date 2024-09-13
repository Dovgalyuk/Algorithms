#include "../LibraryC/array.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Create array and read data from file
Array *array_create_and_read(FILE *input) {
    int n;
    fscanf(input, "%d", &n);
    /* Create array */
    Array *arr = array_create(n, NULL);

    /* Read array data */
    for (int i = 0; i < n; ++i) {
        int *x = (int *)malloc(sizeof(int));
        fscanf(input, "%d", x);
        array_set(arr, i, x);
    }
    return arr;
}

Array *array_create_random(FILE *input) {
    int n;
    fscanf(input, "%d", &n);
    /* Create array */
    Array *arr = array_create(n, NULL);

    return arr;
}

void print_array(const Array *arr) {
    int n = array_size(arr);
    printf("Массив: ");
    for (int i = 0; i < n; ++i) {
        int *value = (int *)array_get(arr, i);
        printf("%d ", *value);
    }
    printf("\n");
}

// Task 1
void task1(Array *arr) {
    srand(time(NULL));

    int n = array_size(arr);
    int sum = 0;

    for (int i = 0; i < n; i++) {
        int *random_height = (int *)malloc(sizeof(int));
        *random_height = rand() % 51 + 150;
        array_set(arr, i, random_height);
        sum += *random_height;
    }

    print_array(arr);

    double average = (double)sum / n;

    int count = 0;
    for (int i = 0; i < n; i++) {
        int *height = (int *)array_get(arr, i);
        if (*height > average) {
            count++;
        }
    }

    printf("Средний рост: %.2f\n", average);
    printf("Количество учеников выше среднего роста: %d\n", count);
}

void task2(Array *arr, FILE *input) {
    int n = array_size(arr);

    // Re-seed the random number generator
    srand(time(NULL));

    for (int i = 0; i < n; ++i) {
        int *random_value = (int *)malloc(sizeof(int));
        *random_value = rand() % 101;
        array_set(arr, i, random_value);
    }

    int a, b;
    // Чтение значений a и b из файла
    fscanf(input, "%d %d", &a, &b);

    int valid_count = 0;

    for (int i = 0; i < n; ++i) {
        int *value = (int *)array_get(arr, i);
        if (*value < a || *value > b) {
            array_set(arr, valid_count++, value);
        } else {
            free(value);
        }
    }

    for (int i = valid_count; i < n; ++i) {
        int *zero_value = (int *)malloc(sizeof(int));
        *zero_value = 0;
        array_set(arr, i, zero_value);
    }

    printf("Сжатый массив: ");
    for (int i = 0; i < n; ++i) {
        int *value = (int *)array_get(arr, i);
        printf("%d ", *value);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Недостаточно аргументов.\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    FILE *input_random = fopen(argv[2], "r");
    if (input == NULL || input_random == NULL) {
        printf("Ошибка открытия файла.\n");
        return 1;
    }

    // Task 1
    Array *arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    
    // Task 2
    arr = array_create_and_read(input);
    task2(arr, input);
    array_delete(arr);

    arr = array_create_random(input_random);
    task1(arr);
    array_delete(arr);

    // Task 3 (random array)
    arr = array_create_random(input_random);
    task2(arr, input_random);
    array_delete(arr);

    fclose(input);
    fclose(input_random);

    return 0;
}
