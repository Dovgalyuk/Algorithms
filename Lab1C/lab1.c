#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Описание структуры динамического массива
typedef struct {
    int *data;
    int size;
} Array;

// Функция для создания массива с фиксированным размером
Array *array_create(int size, int *values) {
    Array *arr = (Array *)malloc(sizeof(Array));
    arr->size = size;
    arr->data = (int *)malloc(size * sizeof(int));

    if (values) {
        for (int i = 0; i < size; ++i) {
            arr->data[i] = values[i];
        }
    }

    return arr;
}

// Функция для удаления массива
void array_delete(Array *arr) {
    if (arr) {
        free(arr->data);
        free(arr);
    }
}

// Функция для установки значения в массив
void array_set(Array *arr, int index, int value) {
    if (index >= 0 && index < arr->size) {
        arr->data[index] = value;
    }
}

// Функция для получения значения из массива
int array_get(const Array *arr, int index) {
    if (index >= 0 && index < arr->size) {
        return arr->data[index];
    }
    return 0; // Можно добавить обработку ошибок
}

// Функция для чтения массива из файла
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

// Задача 1: Печать двузначных и трехзначных чисел
void task1(Array *arr) {
    printf("Двузначные числа:\n");
    for (int i = 0; i < arr->size; ++i) {
        int value = array_get(arr, i);
        if (value >= 10 && value <= 99) {
            printf("%d ", value);
        }
    }
    printf("\nТрехзначные числа:\n");
    for (int i = 0; i < arr->size; ++i) {
        int value = array_get(arr, i);
        if (value >= 100 && value <= 999) {
            printf("%d ", value);
        }
    }
    printf("\n");
}

// Задача 2: Сумма элементов между минимальным и максимальным элементами
void task2(Array *arr) {
    int min = INT_MAX;
    int max = INT_MIN;
    int min_index = 0, max_index = 0;

    // Находим минимальный и максимальный элементы
    for (int i = 0; i < arr->size; ++i) {
        int value = array_get(arr, i);
        if (value < min) {
            min = value;
            min_index = i;
        }
        if (value > max) {
            max = value;
            max_index = i;
        }
    }

    // Убедимся, что минимальный индекс меньше максимального
    if (min_index > max_index) {
        int temp = min_index;
        min_index = max_index;
        max_index = temp;
    }

    // Считаем сумму элементов между минимальным и максимальным
    int sum = 0;
    for (int i = min_index + 1; i < max_index; ++i) {
        sum += array_get(arr, i);
    }

    printf("Сумма элементов между минимальным и максимальным: %d\n", sum);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Использование: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        printf("Ошибка открытия файла\n");
        return 1;
    }

    // Первая задача
    Array *arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    // Вторая задача
    rewind(input);  // Возвращаемся в начало файла
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    fclose(input);
    return 0;
}

