#include "array.h"
#include <iostream>
#include <map>

void task1(Array* arr,int size)
{
    // Заполняем массив случайными числами
    for (int i = 0; i < size; i++)
    {
        arr->data[i] = rand() % 100; // Генерируем случайное число от 0 до 99
    }
    
    for (int i = 0; i < size; i++)
    {
        std::cout << arr->data[i]<<std::endl;
    }

    // Выясняем, верно ли, что сумма элементов, которые больше 20, превышает 100
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr->data[i] > 20)
        {
            sum += arr->data[i];
        }
    }
    if (sum > 100)
    {
        std::cout << "Сумма элементов, которые больше 20, превышает 100" << std::endl;
    }
    else
    {
        std::cout << "Сумма элементов, которые больше 20, не превышает 100" << std::endl;
    }

    // Выясняем, верно ли, что сумма элементов, которые меньше 50, является четным числом
    sum = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr->data[i] < 50)
        {
            sum += arr->data[i];
        }
    }
    if (sum % 2 == 0)
    {
        std::cout << "Сумма элементов, которые меньше 50, является четным числом" << std::endl;
    }
    else
    {
        std::cout << "Сумма элементов, которые меньше 50, не является четным числом" << std::endl;
    }
}


void task2(Array* arr, int size)
{
    // Заполняем массив случайными числами
    for (int i = 0; i < size; i++)
    {
        arr->data[i] = rand() % 100; // Генерируем случайное число от 0 до 99
    }

    // Находим элементы, которые в массиве встречаются только один раз
    std::map<int, int> counts;
    for (int i = 0; i < size; i++)
    {
        counts[arr->data[i]]++;
    }
    for (auto it = counts.begin(); it != counts.end(); ++it)
    {
        if (it->second == 1)
        {
            std::cout << it->first << " встречается только один раз" << std::endl;
        }
    }
}


int main()
{
    setlocale(0, "Russian");
    Array* arr = NULL;

    int i, j;

    // Создаем массив и вызываем task1
    std::cout << "Введите размер и мы создадим первый массив: ";
    std::cin >> i;
    arr = array_create(i);
    task1(arr,i);
    array_delete(arr);

    // Создаем массив и вызываем task2
    std::cout << "Введите размер и мы создадим второй массив: ";
    std::cin >> j;
    arr = array_create(j);
    task2(arr,j);
    array_delete(arr);
}
