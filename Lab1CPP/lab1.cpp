#include <iostream>
#include <fstream>
#include <unordered_map>
#include "array.h"

Array* array_create_and_read(std::ifstream& input) {
    int num;

    if (!(input >> num)) {
        throw std::invalid_argument("Failed to read array size");
    }

    Array* arr = array_create(num);

    for (int i = 0; i < num; ++i) {
        int x;
        if (!(input >> x)) {
            array_delete(arr);
            throw std::invalid_argument("Failed to read number");
        }
        array_set(arr, i, x);
    }
    return arr;
}

void task1(std::ifstream& input) {
    Array* arr = array_create_and_read(input);

    double reciprocalSum = 0.0;
    for (size_t i = 0; i < array_size(arr); ++i) {
        int resistance = array_get(arr, i);
        if (resistance == 0) {
            array_delete(arr);
            throw std::runtime_error("Resistance cannot be zero");
        }
        reciprocalSum += 1.0 / resistance;
    }
    double totalResistance = 1.0 / reciprocalSum;

    std::cout << "Total parallel resistance: " << totalResistance << std::endl;
    array_delete(arr);
}

void task2(std::ifstream& input) {
    Array* arr = array_create_and_read(input);

    std::unordered_map<int, int> frequency;
    for (size_t i = 0; i < array_size(arr); ++i) {
        int value = array_get(arr, i);
        frequency[value]++;
    }

    std::cout << "Unique elements: ";
    for (size_t i = 0; i < array_size(arr); ++i) {
        int value = array_get(arr, i);
        if (frequency[value] == 1) {
            std::cout << value << " ";
        }
    }
    std::cout << std::endl;
    array_delete(arr);
}

int main() {
    std::ifstream input("input.txt");

    task1(input);

    task2(input);
    input.close();
    return 0;
}