#include <iostream>
#include "../LibraryCPP/array.cpp"

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

void arrayProcessing(Array* array) {
    for (int i = 0; i < array_size(array); i++) {
        if (array_get(array, i) % 2 == 0) {
            array_set(array, i, array_get(array, i) * array_get(array, i));
        }
        else {
            array_set(array, i, array_get(array, i) * 2);
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
    Array* array = array_create(size);
    fill(array);
    outputToConsole(array);
    arrayProcessing(array);
    outputToConsole(array);
    return 0;
}