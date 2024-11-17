#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>

#include "array.h"

Array *array_create_and_read(std::ifstream &input)
{
    size_t array_size;
    input >> array_size;

    Array *arr = array_create((size_t)array_size);

    int number = 0;
    size_t index = 0;
    while (input >> number)
    {
        array_set(arr, index, number);
        index++;

        if (index == array_size)
            break;
    }

    return arr;
}

void task1(Array *arr, int m, int n) {
    if (arr == nullptr) {
        std::cerr << "Error: Array is nullptr" << std::endl;
        return;
    }

    for (size_t i = 0; i < array_size(arr); ++i) {
        int num = array_get(arr, i);
        if ((i + 1) % 2 != 0) { // Нечетный индекс
            array_set(arr, i, num - m);
        } else { // Четный индекс
            array_set(arr, i, num + n);
        }
    }

    std::cout << "task_1: ";
    for (size_t i = 0; i < array_size(arr); ++i) {
        std::cout << array_get(arr, i) << (i == array_size(arr) - 1 ? "" : ", ");
    }
    std::cout << std::endl;
}

void task2(Array *arr) {
    if (arr == nullptr) {
        std::cerr << "Error: Array is nullptr" << std::endl;
        return;
    }

    std::map<int, int> counts; // Используем map для подсчета вхождений элементов
    for (size_t i = 0; i < array_size(arr); ++i) {
        counts[array_get(arr, i)]++;
    }

    std::cout << "task_2: ";
    bool first = true;
    for (const auto& pair : counts) {
        if (pair.second == 1) { // Элемент встречается только один раз
            if (!first) std::cout << ", ";
            std::cout << pair.first;
            first = false;
        }
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "args error" << std::endl;
        return 1;
    }

    Array *arr = nullptr;
    std::ifstream input(argv[1]);
    int m, n;

    if (!input) {
        std::cerr << "read file error " << argv[1] << std::endl;
        return 1;
    }

    arr = array_create_and_read(input);
    input >> m >> n; // Считываем m и n из файла после массива

    if(input.fail()){
        std::cerr << "Error reading m and n from file." << std::endl;
        return 1;
    }

    task1(arr, m, n);
    array_delete(arr);


    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    input.close();

    return 0;
}
