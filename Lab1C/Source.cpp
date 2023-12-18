// array.h
#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

struct Array {
    int* data;
    size_t size;
};

Array array_create(size_t size);
void array_set(Array& arr, size_t index, int value);
void array_delete(Array& arr);

#endif // ARRAY_H

// array.cpp
#include "array.h"
#include <cstdlib>

Array array_create(size_t size) {
    Array arr;
    arr.size = size;
    arr.data = new int[size];
    return arr;
}

void array_set(Array& arr, size_t index, int value) {
    if (index < arr.size) {
        arr.data[index] = value;
    }
}

void array_delete(Array& arr) {
    delete[] arr.data;
}

// main.cpp
#include "array.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void processArray(Array& arr, int m, int n) {
    for (size_t i = 0; i < arr.size; i++) {
        if (arr.data[i] % 2 != 0) {
            arr.data[i] -= m;
        }
        if (i % 2 == 0) {
            arr.data[i] += n;
        }
    }
}

void findMaxSum(const Array& arr) {
    int maxSum = 0;
    size_t maxPos = 0; // изменено название переменной на maxPos
    for (size_t i = 0; i < arr.size - 4; i++) {
        int sum = arr.data[i] + arr.data[i + 1] + arr.data[i + 2] + arr.data[i + 3] + arr.data[i + 4];
        if (sum > maxSum) {
            maxSum = sum;
            maxPos = i; // изменено название переменной на maxPos
        }
    }

    std::cout << "Максимальная сумма пяти соседних элементов: " << maxSum << std::endl;
}


void printArray(const Array& arr, const std::string& label) {
    std::cout << label << ": ";
    for (size_t i = 0; i < arr.size; i++) {
        std::cout << arr.data[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    int size, m, n;
    std::cout << "Введите размер массива: ";
    std::cin >> size;
    Array arr = array_create(size);

    // Заполнение массива случайными числами
    for (size_t i = 0; i < arr.size; i++) {
        array_set(arr, i, rand() % 100); // Заполняем случайными числами от 0 до 99
    }

    printArray(arr, "Исходный массив");

    std::cout << "Введите значения m и n: ";
    std::cin >> m >> n;

    processArray(arr, m, n);
    printArray(arr, "Обработанный массив");

    findMaxSum(arr);

    array_delete(arr);

    return 0;
}
