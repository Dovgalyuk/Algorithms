#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Структура динамического массива фиксированного размера
typedef struct {
    int* data;
    int size;
} Array;


// Создание массива фиксированного размера и заполнение данными
Array* array_create(int size) {
    if (size <= 0) {
        printf("Invalid array size\n");
        return NULL;
    }
    Array* arr = (Array*)malloc(sizeof(Array));
    arr->size = size;
    arr->data = (int*)malloc(size * sizeof(int));
    return arr;
}

// Удаление массива
void array_delete(Array* arr) {
    if (arr) {
        free(arr->data);
        free(arr);
    }
}

// Установка значения в массив
void array_set(Array* arr, int index, int value) {
    if (index >= 0 && index < arr->size) {
        arr->data[index] = value;
    }
}

// Получение значения из массива
int array_get(const Array* arr, int index) {
    if (index >= 0 && index < arr->size) {
        return arr->data[index];
    }
    return 0;
}

// Создание массива и чтение его из файла
Array* array_create_and_read(FILE* input) {
    int n;
    if (fscanf(input, "%d", &n) != 1 || n <= 0) {
        printf("Invalid array size\n");
        return NULL;
    }
    Array* arr = array_create(n);

    for (int i = 0; i < n; ++i) {
        int x;
        if (fscanf(input, "%d", &x) != 1) {
            printf("Ошибка при чтении элементов массива\n");
            array_delete(arr);
            return NULL;
        }
        array_set(arr, i, x);
    }

    return arr;
}

// Печать двузначных и трехзначных чисел
void task1(Array* arr) {
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

// Сумма элементов между минимальным и максимальным
void task2(Array* arr) {
    int min = INT_MAX;
    int max = INT_MIN;
    int min_index = 0, max_index = 0;

    // Поиск минимального и максимального элементов
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

    // Убедимся, что min_index < max_index
    if (min_index > max_index) {
        int temp = min_index;
        min_index = max_index;
        max_index = temp;
    }

    int sum = 0;
    for (int i = min_index + 1; i < max_index; ++i) {
        sum += array_get(arr, i);
    }

    printf("Сумма элементов между минимальным и максимальным: %d\n", sum);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Использование: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (!input) {
        printf("Ошибка открытия файла\n");
        return 1;
    }

    // Первая задача
    Array* arr = array_create_and_read(input);
    if (!arr) {
        fclose(input);
        return 1;
    }
    task1(arr);
    array_delete(arr);

    // Вторая задача
    rewind(input);
    arr = array_create_and_read(input);
    if (!arr) {
        fclose(input);
        return 1;
    }
    task2(arr);
    array_delete(arr);

    fclose(input);
    return 0;
}
