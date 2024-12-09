#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "array.h"

// Создание массива и заполнение случайными числами
Array* array_create_and_fill(size_t size) {
    Array* arr = array_create(size);

    for (size_t i = 0; i < size; ++i) {
        int random_value = rand() % 100;
        array_set(arr, i, random_value);
    }

    return arr;
}

// Задание 1: Найти индексы четных элементов
void task1(Array* arr) {
    size_t size = array_size(arr);
    std::cout << "Indexes of even elements: ";
    for (size_t i = 0; i < size; ++i) {
        int value = array_get(arr, i);
        if (value % 2 == 0) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

// Задание 2: Найти элементы, не делящиеся ни на один другой элемент массива
void task2(Array* arr) {
    size_t size = array_size(arr);
    std::cout << "Elements that are not divisible by any other element: ";
    for (size_t i = 0; i < size; ++i) {
        int current_value = array_get(arr, i);
        bool is_divisible = false;
        for (size_t j = 0; j < size; ++j) {
            if (i != j) {
                int other_value = array_get(arr, j);
                if (other_value != 0 && current_value % other_value == 0) {
                    is_divisible = true;
                    break;
                }
            }
        }
        if (!is_divisible) {
            std::cout << current_value << " ";
        }
    }
    std::cout << std::endl;
}

int main(int argc, char **argv) {
    setlocale(LC_ALL, "Rus");
    srand(static_cast<unsigned int>(time(0)));

    size_t size;
    if (argc > 1) {
        // Чтение размера из файла, если передан аргумент
        std::ifstream input(argv[1]);
        if (!input.is_open()) {
            std::cerr << "cant open file: " << argv[1] << '\n';
            return 1;
        }
        input >> size;
    }
    else {
        // Ввод размера с клавиатуры
        std::cout << "enter array size: ";
        std::cin >> size;
    }

    // Создаем массив и заполняем случайными числами
    Array* arr = array_create_and_fill(size);
    if (!arr) {
        std::cout << "error with array read.\n";
        return 1;
    }

    // Выполняем задачи
    task1(arr);
    task2(arr);

    // Удаляем массив
    array_delete(arr);

    return 0;
}