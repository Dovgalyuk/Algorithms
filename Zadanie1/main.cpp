#include <iostream>
#include "array.h"

void Fill(Array* array) {
    for (int i = 0; i < array_size(array); i++) {
        array_set(array, i, rand() % 2001 + (-1000));
    }
}

void Output(Array* array) {
    for (int i = 0; i < array_size(array); i++) {
        std::cout << array_get(array, i) << " ";
    }
    std::cout << "\n";
}

int average_value(Array* array) {
    int sum = 0, number = 0;
    for (int i = 0; i < array_size(array); i++) {
        if (array_get(array, i) > 0) {
            number += 1;
            sum += array_get(array, i);
        }
    }
    return sum / number;
}

int main() {
    std::cout << "input array size: ";
    int size;
    std::cin >> size;
    Array* array = array_create(size);
    Fill(array);
    Output(array);
    std::cout << average_value(array);
    array_delete(array);
    return 0;
}