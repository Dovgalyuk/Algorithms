#include <iostream>
#include <random>
#include "array.h"
#include "array.cpp"

// функция для генерации случайного числа
int random_number(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

int main()
{
    // ввод размера массива
    int size;
    std::cout << "Введите размер массива: ";
    std::cin >> size;

    // проверка на корректность размера массива
    if (size <= 0)
    {
        std::cout << "Некорректный размер массива. Размер массива должен быть положительным числом." << std::endl;
        return 1; // возвращаем код ошибки
    }

    // создание массива с заданным размером
    Array* arr = array_create(size);

    // заполнение массива случайными числами
    for (int i = 0; i < size; ++i)
    {
        array_set(arr, i, random_number(1, 100));
    }

    // вывод исходного массива
    std::cout << "Исходный массив: ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << std::endl;

    // ввод чисел k1 и k2
    int k1, k2;
    std::cout << "Введите индекс k1: ";
    std::cin >> k1;
    std::cout << "Введите индекс k2: ";
    std::cin >> k2;

    // проверка на корректность индексов
    if (k1 < 0 || k1 >= size || k2 < 0 || k2 >= size)
    {
        std::cout << "Некорректные индексы. Индексы должны быть в диапазоне от 0 до " << size - 1 << "." << std::endl;
        array_delete(arr); // освобождаем память
        return 1; // возвращаем код ошибки
    }

    // вычитание элементов массива
    for (int i = 0; i < size; ++i)
    {
        if (array_get(arr, i) > 0)
        {
            array_set(arr, i, array_get(arr, i) - array_get(arr, k1));
        }
        else
        {
            array_set(arr, i, array_get(arr, i) - array_get(arr, k2));
        }
    }

    // вывод измененного массива
    std::cout << "Измененный массив: ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << std::endl;

    // освобождение памяти
    array_delete(arr);

    return 0;
}
