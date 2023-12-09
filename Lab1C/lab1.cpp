#include <stdio.h>
#include "array.h"
#include <stdlib.h>
#include <locale.h>
#include <iostream>

void task1(Array* arr)
{
    // Задача 1: Найти сумму элементов массива, значение которых не превышает 20.
    size_t size = array_size(arr);
    int summ = 0;

    for (size_t i = 0; i < size; ++i)
    {
        if (array_get(arr, i) <= 20)
        {
            summ += array_get(arr, i);
        }

        //Выводим сумму элементов
        printf("%d", summ);
    }
}

    // Задача 2: Найти пять соседних элементов, сумма значений которых максимальна.
void task2(Array* arr)
{
   
    size_t size = array_size(arr);
    int max = -1;

    //проверяем удовлетворимость условию задачи
    if (size >= 5){

        for (size_t i = 4; i < size; ++i){
            int summ = array_get(arr, i-4) + array_get(arr, i-3) + array_get(arr, i-2) + array_get(arr, i-1) array_get(arr, i);
            if (summ > max){
                max = summ;
            }
        }
        printf("%d", max);
    }
    else {
        printf("Длина массива меньше 5");
    }
}


int main()
{
    setlocale(LC_ALL, "ru");
    Array* arr = NULL;
    size_t size;
    
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

    // Вызов задачи 2
    task2(arr);

    // Удаление второго массива
    array_delete(arr);

    return 0;
}
