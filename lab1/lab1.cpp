#include <iostream>
#include <cstdlib>
#include <ctime>
#include "array.h"

Array* array_create_and_read(std::ifstream& input)
{
    size_t n;
    input >> n;

    Array* arr = new Array(n); 

    for (size_t i = 0; i < n; ++i)
    {
        int x;
        input >> x;
        arr->set(i, x); 
    }
    return arr;
}

Array* array_create_and_fill_random(int size) {
    Array* arr = new Array(size); 

    for (int i = 0; i < size; ++i) {
        int random_value = rand() % 100;
        arr->set(i, random_value);
    }

    return arr;
}

// Задание 1: Найти индексы четных элементов
void task1(Array* arr) {
    int size = arr->size();

    Array* even_indices = new Array(size);
    int even_count = 0;

    for (int i = 0; i < size; ++i) {
        int value = arr->get(i);
        if (value % 2 == 0) {
            even_indices->set(even_count, i); 
            even_count++;
        }
    }

    std::cout << "Индексы четных элементов: ";
    for (int i = 0; i < even_count; ++i) {
        std::cout << even_indices->get(i) << " ";
    }
    std::cout << std::endl;

    delete even_indices;
}

// Задание 2: Найти элементы, не делящиеся ни на один другой элемент массива
void task2(Array* arr) {
    int size = arr->size();

    std::cout << "Элементы, не делящиеся ни на какой другой элемент: ";

    for (int i = 0; i < size; ++i) {
        int current_value = arr->get(i);
        bool is_divisible = false;

        for (int j = 0; j < size; ++j) {
            if (i != j) {
                int other_value = arr->get(j);
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

int main() {
    srand(static_cast<unsigned int>(time(0))); 

    if (!input.is_open()) {
        std::cerr << "Failed to open file: " << "\n";
        return 1;
    }

    Array* arr = array_create_and_read(input);

    // Задача 1
    std::cout << "Введите размер массива для задачи 1: ";
    int size1;
    std::cin >> size1;
    Array* arr1 = array_create_and_fill_random(size1);
    task1(arr1);
    delete arr1;

    // Задача 2
    std::cout << "Введите размер массива для задачи 2: ";
    int size2;
    std::cin >> size2;
    Array* arr2 = array_create_and_fill_random(size2);
    task2(arr2);
    delete arr2; 

    return 0;
}