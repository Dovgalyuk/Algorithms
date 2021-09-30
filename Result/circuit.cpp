//
// Created by KirilliriK on 04.09.2021.
//

#include <iostream>
#include <random>
#include <array.h>

void generateCircuit(Array *array);

int main() {
    int arraySize = 0;
    std::cout << "Enter circuit size: " << std::endl;
    std::cin >> arraySize;
    Array *array = array_create(arraySize);
    generateCircuit(array);

    double result = 0;
    for (size_t i = 0; i < array_size(array); i++) {
        result += 1.0 / array_get(array, i);
    }
    result = std::pow(result, -1);

    std::cout << "Total circuit resistance: " << result << std::endl;
    return 0;
}

void generateCircuit(Array *array) {
    std::random_device randomDevice;
    std::mt19937 randomAlgorithm(randomDevice());
    std::uniform_int_distribution<int> dist(1, 50);

    for (size_t i = 0; i < array_size(array); i++) {
        array_set(array, i, dist(randomAlgorithm));
    }
}