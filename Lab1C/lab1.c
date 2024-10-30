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
    if (arr == NULL) {
        perror("Ошибка выделения памяти для массива");
        return NULL;
    }
    
    arr->size = size;
    arr->data = (int *)malloc(size * sizeof(int));
    if (arr->data == NULL) {
        free(arr);
        perror("Ошибка выделения памяти для массива данных");
        return NULL;
    }

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
    if (index < 0 || index >= arr->size) {
        fprintf(stderr, "Индекс выходит за границы массива\n");
        return 0;
    }
    return arr->data[index];
}

// Функция для чтения массива из файла
Array *array_create_and_read(FILE *input) {
    int n;
    if (fscanf(input, "%d", &n) != 1) {
        fprintf(stderr, "Ошибка чтения количества элементов\n");
        return NULL;
    }
    
    Array *arr = array_create(n, NULL);
    if (arr == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; ++i) {
        int x;
        if (fscanf(input, "%d", &x) != 1) {
            fprintf(stderr, "Ошибка чтения элемента массива\n");
            array_delete(arr);
            return NULL;
        }
        
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

    // Проверим, что минимальный и максимальный индексы различны
    if (min_index == max_index) {
        printf("Все элементы равны, сумма между минимальным и максимальным равна 0\n");
        return;
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
    if (arr == NULL) {
        fclose(input);
        return 1;
    }
    task1(arr);
    array_delete(arr);

    // Вторая задача
    rewind(input);  // Возвращаемся в начало файла
    arr = array_create_and_read(input);
    if (arr == NULL) {
        fclose(input);
        return 1;
    }
    task2(arr);
    array_delete(arr);

    fclose(input);
    return 0;
}
