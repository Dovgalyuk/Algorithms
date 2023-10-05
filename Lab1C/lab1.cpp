#include <stdio.h>
#include "array.h"

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

void task2(Array* arr)
{
    // Задача 2: в какую декаду месяца выпало больше всего осадков
    int maxDecadeSum = 0;
    size_t maxDecadeStartIndex = 0;
    size_t size = array_size(arr);

    for (size_t i = 0; i < size; i += 10)
    {
        int decadeSum = 0;
        for (size_t j = i; j < i + 10 && j < size; ++j)
        {
            decadeSum += array_get(arr, j);
        }
        if (decadeSum > maxDecadeSum)
        {
            maxDecadeSum = decadeSum;
            maxDecadeStartIndex = i;
        }
    }

    printf("Декада с наибольшим количеством осадков: ");
    for (size_t i = maxDecadeStartIndex; i < maxDecadeStartIndex + 10 && i < size; ++i)
    {
        printf("%d ", array_get(arr, i));
    }
    printf("\n");
}

int main()
{
    Array* arr = NULL;
    size_t size;

    // Ввод размера массива с клавиатуры
    printf("Введите размер массива: ");
    scanf("%zu", &size);

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
    scanf("%zu", &size);

    // Создание нового массива и заполнение его случайными данными
    arr = array_create(size);
    for (size_t i = 0; i < size; ++i)
    {
        array_set(arr, i, rand() % 100); // Генерация случайного числа от 0 до 99
    }

    // Вызов задачи 2
    task2(arr);

    // Удаление второго массива
    array_delete(arr);

    return 0;
}