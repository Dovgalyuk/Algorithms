#include <stdio.h>
#include <stdlib.h>
#include "array.h"

// Создать массив и считать данные из файла
Array* array_create_and_read(FILE* input)
{
    int n;
    fscanf(input, "%d", &n);  // Считываем размер массива

    /* Создаем массив */
    Array* arr = array_create(n, NULL);
    if (arr == NULL) return NULL;  // Проверяем успешность создания массива

    /* Считываем элементы массива */
    for (int i = 0; i < n; ++i)
    {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, x);
    }
    return arr;
}

// Задача 1: Найти количество элементов, превышающих сумму всех элементов массива
void task1(Array* arr)
{
    int sum = 0;

    // Считаем сумму всех элементов массива
    for (size_t i = 0; i < array_size(arr); i++) {
        sum += array_get(arr, i);
    }

    printf("Сумма всех элементов массива: %d\n", sum);
    printf("Элементы, большие суммы: ");

    // Выводим элементы, превышающие сумму всех элементов массива
    for (size_t i = 0; i < array_size(arr); i++) {
        if (array_get(arr, i) > sum) {
            printf("%d (index: %zu) ", array_get(arr, i), i);
        }
    }
    printf("\n");
}

// Задача 2: Сдвиг элементов массива в указанном направлении
void task2(Array* arr)
{
    int steps;
    char direction;

    printf("Введите количество шагов для сдвига: ");
    scanf("%d", &steps);

    printf("Введите направление сдвига (L - влево, R - вправо): ");
    scanf(" %c", &direction);

    size_t size = array_size(arr);

    // Выполняем сдвиг массива
    for (int step = 0; step < steps; step++) {
        if (direction == 'R') {  // Сдвиг вправо
            int last = array_get(arr, size - 1);
            for (size_t i = size - 1; i > 0; i--) {
                array_set(arr, i, array_get(arr, i - 1));
            }
            array_set(arr, 0, 0);  // Освобождаем первую ячейку
        }
        else if (direction == 'L') {  // Сдвиг влево
            for (size_t i = 0; i < size - 1; i++) {
                array_set(arr, i, array_get(arr, i + 1));
            }
            array_set(arr, size - 1, 0);  // Освобождаем последнюю ячейку
        }

        // Выводим состояние массива после сдвига
        printf("Массив после %d шага: ", step + 1);
        for (size_t i = 0; i < size; i++) {
            printf("%d ", array_get(arr, i));
        }
        printf("\n");
    }
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("Ошибка: укажите файл с входными данными.\n");
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Ошибка: не удалось открыть файл %s.\n", argv[1]);
        return 1;
    }

    // Выполняем задачу 1
    Array* arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    // Выполняем задачу 2
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    fclose(input);
    return 0;
}