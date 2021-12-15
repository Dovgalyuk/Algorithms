#include <iostream>
#include "array.h"

int writeNumber() {
    int number;
    std::cout << "input number ";
    std::cin >> number;
    return number;
}

void fill(Array* array) {
    for (int i = 0; i < array_size(array); i++) {
        array_set(array, i, rand() % 1000);
    }
}

void arrayProcessing(Array* array, int n, int m) {
    for (int i = 0; i < array_size(array); i++) {
        if (array_get(array, i) % 2 != 0) {
            array_set(array, i, array_get(array, i) - m);
        }
        if ((i + 1) % 2 != 0) {
            array_set(array, i, array_get(array, i) + n);
        }
    }
}


void outputToConsole(Array* array) {
    for (int i = 0; i < array_size(array); i++) {
        std::cout << array_get(array, i) << " ";
    }
    std::cout << "\n";
}

int main() {

    int size = writeNumber();
    std::cout << "n ";
    int n = writeNumber();
    std::cout << "m ";
    int m = writeNumber();
    Array* array = array_create(size);
    fill(array);
    outputToConsole(array);
    arrayProcessing(array, n, m);
    outputToConsole(array);
    array_delete(array);
    return 0;
}