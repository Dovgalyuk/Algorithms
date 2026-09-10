#include <iostream>
#include <fstream>
#include "array.h"

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

    // Получение размера массива
    size_t size = array_size(arr);
    if (size == 0)
    {
        // Если массив пустой - освобождение памяти и завершение программы
        array_delete(arr);
        return 0;
    }

    // RLE-сжатие - группировка подряд идущих одинаковых элементов
    // current — текущее значение группы, count — количество повторов
    Data current = array_get(arr, 0);
    int count = 1;

    // Проход по массиву начиная со второго элемента
    for (size_t i = 1; i < size; ++i)
    {
        Data val = array_get(arr, i);
        if (val == current)
        {
            // Если элемент совпадает с текущим — увеличивается счётчик количества повторов
            ++count;
        }
        else
        {
            // Элемент отличается — выводится группа (значение, количество)
            std::cout << current << ' ' << count << ' ';
            // Начинается новая группа
            current = val;
            count = 1;
        }
    }
    // Вывод последней группы
    std::cout << current << ' ' << count << std::endl;

    // Освобождение памяти выделенной под массив
    array_delete(arr);
    return 0;
}