#include <iostream>
#include <random>
#include "array.h"

// функция для генерации случайного числа
int random_number(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

void task1(Array* arr)
{
    // вывод исходного массива
    std::cout << "Исходный массив: ";
    for (size_t i = 0; i < array_size(arr); ++i)
    {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << std::endl;

    // ввод чисел k1 и k2
    size_t k1, k2;
    std::cout << "Введите индекс k1: ";
    std::cin >> k1;
    std::cout << "Введите индекс k2: ";
    std::cin >> k2;

    // вычитание элементов массива
    for (size_t i = 0; i < array_size(arr); ++i)
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
    for (size_t i = 0; i < array_size(arr); ++i)
    {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << std::endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    // ввод размера массива
    size_t size;
    std::cout << "Введите размер массива: ";
    std::cin >> size;

    // создание массива с заданным размером
    Array* arr = array_create(size);

    // заполнение массива случайными числами
    for (size_t i = 0; i < size; ++i)
    {
        array_set(arr, i, random_number(1, 100));
    }

    task1(arr);

    // освобождение памяти
    array_delete(arr);

    return 0;
}
