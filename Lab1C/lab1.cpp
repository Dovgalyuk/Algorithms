#include <iostream>
#include <cstdlib>
#include <ctime>
#include "array.h"
#include "array.cpp"
// Функция для задачи 1
void task1(Array* arr, int k1, int k2)
{
    // Перебираем все элементы массива
    for (size_t i = 0; i < array_size(arr); ++i)
    {
        // Если элемент положительный
        if (array_get(arr, i) > 0)
        {
            // Если текущий индекс равен k1, то заменяем элемент на k2
            if (i == k1)
            {
                array_set(arr, i, array_get(arr, k2));
            }
            // Иначе заменяем элемент на k1
            else
            {
                array_set(arr, i, array_get(arr, k1));
            }
        }
    }
}

// Функция для задачи 2
void task2(Array* arr)
{
    // Инициализируем максимальную сумму и индекс начала подмассива
    int maxSum = 0;
    int startIndex = 0;
    // Перебираем все подмассивы размером 5
    for (size_t i = 0; i < array_size(arr) - 4; ++i)
    {
        int currentSum = 0;
        // Вычисляем сумму текущего подмассива
        for (size_t j = i; j < i + 5; ++j)
        {
            currentSum += array_get(arr, j);
        }
        // Если текущая сумма больше максимальной, то обновляем максимальную сумму и индекс начала подмассива
        if (currentSum > maxSum)
        {
            maxSum = currentSum;
            startIndex = i;
        }
    }
    // Выводим пять соседних элементов с максимальной суммой
    std::cout << "Пять соседних элементов с максимальной суммой: ";
    for (size_t i = startIndex; i < startIndex + 5; ++i)
    {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << std::endl;
}

int main()
{
    // Инициализируем генератор случайных чисел
    srand(time(0));
    int n;
    // Вводим размер массива
    std::cout << "Введите размер массива: ";
    std::cin >> n;
    // Создаем массив
    Array* arr1 = array_create(n);
    // Заполняем массив случайными числами
    for (size_t i = 0; i < n; ++i)
    {
        array_set(arr1, i, rand() % 100);
    }
    // Вводим k1 и k2
    int k1, k2;
    std::cout << "Введите k1 и k2: ";
    std::cin >> k1 >> k2;
    // Выполняем задачу 1
    task1(arr1, k1, k2);
    // Выводим результат
    for (size_t i = 0; i < n; ++i)
    {
        std::cout << array_get(arr1, i) << " ";
    }
    std::cout << std::endl;
    // Удаляем массив
    array_delete(arr1);

    // Повторяем процесс для второго массива
    std::cout << "Введите размер массива: ";
    std::cin >> n;
    Array* arr2 = array_create(n);
    for (size_t i = 0; i < n; ++i)
    {
        array_set(arr2, i, rand() % 100);
    }
    task2(arr2);
    array_delete(arr2);

    return 0;
}
