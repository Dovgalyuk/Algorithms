#include <iostream>
#include <fstream>
#include "array.h"

// Вычисление факториала, если n<0 - возвращается 0
long long factorial(int n)
{
    if (n < 0)
        return 0;
    long long res = 1;
    for (int i = 2; i <= n; ++i)
        res *= i;
    return res;
}

int main(int argc, char **argv)
{
    //Поток для чтения файла
    std::ifstream in;
    if (argc > 1)
    {
        // если передан аргумент - это имя файла
        in.open(argv[1]);
        if (!in.is_open())
        {
            std::cerr << "Ошибка при открытии файла: " << argv[1] << std::endl;
            return 1;
        }
    }
    else
    {
        // завершение если имя файла не передано
        return 0;
    }

    // Чтение размера массива из первой строки
    int n = 0;
    if (!(in >> n) || n <= 0)
    {
        std::cerr << "Неккоректный размер" << std::endl;
        return 1;
    }

    // Создание динамического массива размером n
    Array *arr = array_create(static_cast<size_t>(n));

    // Заполнение числами из файла
    for (int i = 0; i < n; ++i)
    {
        // если чисел не хватает, недостающие равны 0
        int x = 0;
        if (!(in >> x))
            x = 0;
        array_set(arr, static_cast<size_t>(i), static_cast<Data>(x));
    }

    // Замена каждого числа на его факториал
    for (size_t i = 0; i < array_size(arr); ++i)
    {
        Data val = array_get(arr, i);
        //вычисление факториала
        long long f = factorial(static_cast<int>(val));
        //результат записывается обратно в массив
        array_set(arr, i, static_cast<Data>(f));
    }

    // Вывод элементов массива в одну строку через пробел
    for (size_t i = 0; i < array_size(arr); ++i)
    {
        if (i > 0)
            std::cout << ' ';
        std::cout << array_get(arr, i);
    }
    std::cout << std::endl;

    // Освобождение памяти выделенной под массив
    array_delete(arr);
    return 0;
}