#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "array.h"

Array* array_create_and_read(std::ifstream& input) {
    size_t n;
    input >> n;

    Array* arr = array_create(n);

    for (size_t i = 0; i < n; ++i) {
        int x;
        input >> x; 
        array_set(arr, i, x); 
    }
    return arr;
}

Array* array_create_and_fill_random(int size) {
    Array* arr = array_create(size);  

    for (int i = 0; i < size; ++i) {
        int random_value = rand() % 100;
        array_set(arr, i, random_value); 
    }

    return arr;
}


void task1(Array* arr) {
    size_t size = array_size(arr); 

    Array* even_indices = array_create(size); 
    int even_count = 0;

    for (size_t i = 0; i < size; ++i) {
        int value = array_get(arr, i); 
        if (value % 2 == 0) {
            array_set(even_indices,i, even_count);
            even_count++;
        }
    }

    std::cout << "Индексы четных элементов: ";
    for (int i = 0; i < even_count; ++i) {
        std::cout << array_get(even_indices, i) << " ";
    }
    std::cout << std::endl;

    array_delete(even_indices);
}

// Задание 2: Найти элементы, не делящиеся ни на один другой элемент массива
void task2(Array* arr) {
    size_t size = array_size(arr); 
    std::cout << "Элементы, не делящиеся ни на какой другой элемент: ";
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

int main() {
    srand(static_cast<unsigned int>(time(0))); 

    std::ifstream input("input.txt");
    if (!input.is_open()) {
        std::cerr << "Не удалось открыть файл." << std::endl;
        return 1;
    }

    Array* arr = array_create_and_read(input); 
    input.close();

    // Задача 1
    std::cout << "Введите размер массива для задачи 1: ";
    int size1;
    std::cin >> size1;
    Array* arr1 = array_create_and_fill_random(size1);
    task1(arr1);
    array_delete(arr1);

    // Задача 2
    std::cout << "Введите размер массива для задачи 2: ";
    int size2;
    std::cin >> size2;
    Array* arr2 = array_create_and_fill_random(size2);
    task2(arr2); 
    array_delete(arr2);

    array_delete(arr);

    return 0;
}