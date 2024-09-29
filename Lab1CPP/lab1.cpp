#include <iostream>
#include <fstream>
#include <unordered_map>
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

// Task 1: Сумма чётных положительных элементов массива
void task1(std::ifstream& input) {
    Array* arr = array_create_and_read(input);

    int sum = 0;
    for (size_t i = 0; i < array_size(arr); ++i) {
        int value = array_get(arr, i);
        if (value > 0 && value % 2 == 0) {
            sum += value;
        }
    }

    std::cout << "Sum of even positive elements: " << sum << std::endl;
    array_delete(arr);
}

// Task 2: Элементы, которые не делятся на другие элементы массива
void task2(std::ifstream& input) {
    Array* arr = array_create_and_read(input);

    std::cout << "Elements that are not divisible by any other element: ";
    bool found = false;

    for (size_t i = 0; i < array_size(arr); ++i) {
        int value = array_get(arr, i);
        bool divisible = false;

        for (size_t j = 0; j < array_size(arr); ++j) {
            if (i != j && array_get(arr, j) != 0 && value % array_get(arr, j) == 0) {
                divisible = true;
                break;
            }
        }

        if (!divisible) {
            std::cout << value << " ";
            found = true;
        }
    }

    if (!found) {
        std::cout << "None found.";
    }

    std::cout << std::endl;
    array_delete(arr);
}

int main() {
   std::ifstream input("input.txt");

    if (!input.is_open()) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return 1;
    }

    task1(input);

    input.clear();
    input.seekg(0);

    task2(input);

    input.close();
    return 0;
}


