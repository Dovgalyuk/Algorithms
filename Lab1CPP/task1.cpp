#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

int main(int argc, char* argv[])
{
    const char* filename = "input.txt";

    if (argc > 1)
    {
        filename = argv[1];
    }

    ifstream input(filename);

    if (!input.is_open())
    {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return 1;
    }

    // Считываем размер первого массива
    size_t n;
    input >> n;

    // Создаём первый массив
    Array* arr = array_create(n);

    // Заполняем первый массив числами из файла
    for (size_t i = 0; i < n; i++)
    {
        Data value;
        input >> value;

        array_set(arr, i, value);
    }

    input.close();

    // Считаем количество чётных элементов
    size_t evenCount = 0;

    for (size_t i = 0; i < array_size(arr); i++)
    {
        if (array_get(arr, i) % 2 == 0)
        {
            evenCount++;
        }
    }

    // Создаём второй массив.
    // Его размер равен количеству чётных элементов.
    Array* indexes = array_create(evenCount);

    // Записываем индексы чётных элементов
    size_t j = 0;

    for (size_t i = 0; i < array_size(arr); i++)
    {
        if (array_get(arr, i) % 2 == 0)
        {
            array_set(indexes, j, static_cast<Data>(i));
            j++;
        }
    }

    // Вывод первого массива
    cout << "Первый массив:" << endl;

    for (size_t i = 0; i < array_size(arr); i++)
    {
        cout << array_get(arr, i) << " ";
    }

    cout << endl;

    // Вывод второго массива
    cout << "Индексы четных элементов:" << endl;

    for (size_t i = 0; i < array_size(indexes); i++)
    {
        cout << array_get(indexes, i) << " ";
    }

    cout << endl;

    // Освобождаем память
    array_delete(arr);
    array_delete(indexes);

    return 0;
}