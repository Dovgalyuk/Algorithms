#include <iostream>
#include <random>
#include "array.h"

void task1(Array* arr)
{
    // этот метод создает псевдорандомные числа от 1 до 100
    std::mt19937 mt(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 100);

    for (int i = 0; i < arr->size; i++) {
        arr->dynamArray[i] = dist(mt); // элементу присваивается число от 1 до 100
    }

    std::cout << "\n\nПервый массив: ";
    for (int i = 0; i < arr->size; i++) {
        std::cout << arr->dynamArray[i] << " ";
    }

    int min1 = arr->dynamArray[0];
    int m = 0; // в будущем номер первого минимального массива
    for (int i = 0; i < arr->size; i++) {
        if (arr->dynamArray[i] < min1)
        {
            min1 = arr->dynamArray[i];
            m = i;
        }
    }

    int min2 = (m == 0) ? arr->dynamArray[1] : arr->dynamArray[0]; // int min2 = arr1->dynamArray[0] не дает пропускать нулевой индекс
    for (int i = 0; i < arr->size; i++) {
        if (i == m)
        {
            continue;
        }
        if (arr->dynamArray[i] < min2)
        {
            min2 = arr->dynamArray[i];
        }

    }
    std::cout << "\nДва наименьших элемента массива: " << min1 << " " << min2 << std::endl;
}

void task2(Array* arr)
{
    // этот метод создает псевдорандомные числа от 1 до 100
    std::mt19937 mt(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 100);

    for (int i = 0; i < arr->size; i++) {
        arr->dynamArray[i] = dist(mt); // элементу присваивается число от 1 до 100
    }

    std::cout << "\n\n======================================================\n\nВторой массив: ";
    for (int i = 0; i < arr->size; i++) {
        std::cout << arr->dynamArray[i] << " ";
    }

    int m = arr->size; // чтобы считать с конца индексы в массиве 

    std::cout << "Укажите в какую сторону сдвинуть массив? (введите стрелку)\n\nВлево  ' < '   ||   ' > '  Вправо\n";
    char a; std::cin >> a;
    std::cout << std::endl << "Шагов для сдвига массива: ";
    int b, size = arr->size; std::cin >> b;

    if (a == '<') {
        std::cout << std::endl << "Сдвиг влево - " << b << " шага(-ов): \n";

        for (int j = 0; j < b; j++) {

            for (int i = 0; i < size - 1; i++) { // сдвиг влево
                arr->dynamArray[i] = arr->dynamArray[i + 1];
            }

            arr->dynamArray[size - 1] = 0; // обнуление слева

            std::cout << "Шаг " << j + 1 << ": ";
            for (int i = 0; i < size; i++) {
                std::cout << arr->dynamArray[i] << " ";
            }
            std::cout << std::endl;
        }
    }

    else if (a == '>') {
        std::cout << std::endl << "Сдвиг вправо - " << b << " шага(-ов): \n";
        for (int j = 0; j < b; j++) {

            for (int i = size - 1; i > 0; i--) { // сдвиг вправо
                arr->dynamArray[i] = arr->dynamArray[i - 1];
            }

            arr->dynamArray[0] = 0; // обнуление справа

            std::cout << "Шаг " << j + 1 << ": ";
            for (int i = 0; i < size; i++) {
                std::cout << arr->dynamArray[i] << " ";
            }
            std::cout << std::endl;
        }
    }

    std::cout << std::endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int size = 0;
    std::cout << "Задайте размер массива: "; std::cin >> size;
    Array* arr = array_create(size);

    /* Create array here */
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    Array* arr = array_create(size);
    task2(arr);
    array_delete(arr);
    return 0;
}
