#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include "array.h"

void task1(Array* arr)
{
    int size;
    printf("Введите размер массива: ");
    scanf("%d", &size);
    arr = array_create(size);

    srand(time(0));
    int sum1 = 0;
    int sum2 = 0;
    for (int i = 0; i < size; i++) {
        int num = rand() % 100; // генерируем случайное число от 0 до 99
        array_set(arr, i, num);
        if (num > 20) sum1 += num;
        if (num < 50) sum2 += num;
    }

    printf("Сумма элементов, которые больше 20: %d\n", sum1);
    printf("Сумма элементов, которые меньше 50: %d\n", sum2);
}

void task2(Array* arr)
{
    int size;
    printf("Введите размер массива: ");
    scanf("%d", &size);
    arr = array_create(size);

    srand(time(0));
    for (int i = 0; i < size; i++) {
        int num = rand() % 100; // генерируем случайное число от 0 до 99
        array_set(arr, i, num);
    }

    // Находим элементы, которые в массиве встречаются только один раз
    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (array_get(arr, i) == array_get(arr, j)) {
                count++;
            }
        }
        if (count == 1) {
            printf("%d ", array_get(arr, i));
        }
    }
    printf("\n");
}

int main()
{
    Array* arr = NULL;
    /* Создаем массив */
    task1(arr);
    array_delete(arr);
    /* Создаем другой массив */
    task2(arr);
    array_delete(arr);
}
