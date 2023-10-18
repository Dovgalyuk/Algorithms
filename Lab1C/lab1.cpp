#include <stdio.h>
#include "array.h"
#include <stdlib.h>
#include <locale.h>
#include <iostream>

void task1(Array* arr)
{
    // Задача 1: в какой период выпало больше осадков: в первую половину июня или во вторую
    int firstHalfSum = 0;
    int secondHalfSum = 0;
    size_t size = array_size(arr);

    for (size_t i = 0; i < size; ++i)
    {
        if (i < size / 2)
        {
            firstHalfSum += array_get(arr, i);
        }
        else
        {
            secondHalfSum += array_get(arr, i);
        }
    }

    if (firstHalfSum > secondHalfSum)
    {
        printf("Больше осадков выпало в первую половину июня\n");
    }
    else if (secondHalfSum > firstHalfSum)
    {
        printf("Больше осадков выпало во вторую половину июня\n");
    }
    else
    {
        printf("Осадки равномерно распределены между первой и второй половинами июня\n");
    }
}

void shiftArray(Array* arr, size_t steps, int direction)
{
   
    size_t size = array_size(arr);

    

    // Сдвиг вправо
    if (direction == 1)
    {
        for (size_t i = 0; i < steps; ++i)
        {

            for (size_t j = size - 1; j > 0; --j)
            {
                array_set(arr, j, array_get(arr, j - 1)); // Сдвигаем элементы вправо
            }

            array_set(arr, 0, 0); // 0 на первую позицию

            // Выводим массив после каждого шага
            printf("Шаг %ld: ", i + 1);
            for (size_t k = 0; k < size; ++k)
            {
                printf("%d ", array_get(arr, k));
            }
            printf("\n");
        }
    }

    // Сдвиг влево
    if (direction == -1)
    {
        for (size_t i = 0; i < steps; ++i)
        {

            for (size_t j = 0; j < size - 1; ++j)
            {
                array_set(arr, j, array_get(arr, j + 1)); // Сдвигаем элементы влево
            }

            array_set(arr, size - 1, 0); // 0 на последнюю позицию

            // Выводим массив после каждого шага
            printf("Шаг %ld: ", i + 1);
            for (size_t k = 0; k < size; ++k)
            {
                printf("%d ", array_get(arr, k));
            }
            printf("\n");
        }
    }
}


int main()
{
    setlocale(LC_ALL, "ru");
    Array* arr = NULL;
    size_t size;
    size_t direct;
    size_t step;
    // Ввод размера массива с клавиатуры
    printf("Введите размер массива: ");
    if (scanf("%zu", &size) != 1) {
        printf("Ошибка ввода размера.\n");
        return 1;
    }
    // Создание массива и заполнение его случайными данными
    arr = array_create(size);
    for (size_t i = 0; i < size; ++i)
    {
        array_set(arr, i, rand() % 100); // Генерация случайного числа от 0 до 99
    }

    // Вызов задачи 1
    task1(arr);

    // Удаление массива
    array_delete(arr);

    // Ввод размера нового массива с клавиатуры
    printf("Введите размер нового массива: ");
    if (scanf("%zu", &size) != 1) {
        printf("Ошибка ввода размера.\n");
        return 1;
    }
    // Создание нового массива и заполнение его случайными данными
    arr = array_create(size);
    for (size_t i = 0; i < size; ++i)
    {
        array_set(arr, i, rand() % 100); // Генерация случайного числа от 0 до 99
    }

     if (scanf("%zu", &direct) != 1 && (size_t)direct != -1)
    {
        printf("Неверно указано направление сдвига\n");
        return 1;
    }
     if (scanf("%zu", &step) <= 0 || (size_t)step >= size)
    {
        printf("Неверное количество шагов\n");
        return 1;
    }
    // Вызов задачи 2
    shiftArray(arr, step, direct);

    // Удаление второго массива
    array_delete(arr);

    return 0;
}
