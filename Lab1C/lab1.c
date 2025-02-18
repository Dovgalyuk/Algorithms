#include <stdio.h>
#include "../LibraryC/array.h"

// Задача 1: Найти количество элементов, превышающих сумму всех элементов массива
void task1(Array* arr) {
    int sum = 0;
    
    // Считаем сумму всех элементов массива
    for (size_t i = 0; i < array_size(arr); i++) {
        sum += array_get(arr, i);
    }

    printf("Сумма всех элементов массива: %d\n", sum);
    printf("Элементы, большие суммы: ");
    
    // Выводим элементы, которые больше суммы всех элементов
    for (size_t i = 0; i < array_size(arr); i++) {
        if (array_get(arr, i) > sum) {
            printf("%d (index: %zu) ", array_get(arr, i), i);
        }
    }
    printf("\n");
}

// Задача 2: Сдвиг элементов массива в указанном направлении
void task2(Array* arr) {

}

int main(int argc, char **argv) {
    int n;
    printf("Введите размер массива: ");
    scanf("%d", &n);

    // Создаем массив
    Array *arr = array_create(n, NULL);
    
    // Заполняем массив случайными числами
    for (size_t i = 0; i < n; i++) {
        array_set(arr, i, rand() % 100);  // Используем rand для генерации случайных чисел
    }

    // Выводим исходный массив
    printf("Исходный массив: ");
    for (size_t i = 0; i < n; i++) {
        printf("%d ", array_get(arr, i));
    }
    printf("\n");

    // Выполняем задачи
    task1(arr);
    task2(arr);

    // Освобождаем память
    array_delete(arr);
    return 0;
}