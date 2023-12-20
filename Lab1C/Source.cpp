// array.h
#ifndef ARRAY_H
#define ARRAY_H


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
    if (arr.size < 5) {
        std::cout << "Массив слишком мал для вычисления максимальной суммы пяти соседних элементов." << std::endl;
        return;
    }

    int currentSum = 0;

    // Вычисляем начальную сумму первых пяти элементов
    for (size_t i = 0; i < 5; i++) {
        currentSum += arr.data[i];
    }

    int maxSum = currentSum;

    // Проходимся по массиву, обновляя сумму на каждой итерации
    for (size_t i = 5; i < arr.size; i++) {
        // Добавляем новый элемент
        currentSum += arr.data[i];
        // Удаляем самый старый элемент (те, что за пределами "скользящего окна")
        currentSum -= arr.data[i - 5];

        // Обновляем максимальную сумму при необходимости
        if (currentSum > maxSum) {
            maxSum = currentSum;
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
    Array* arr = array_create(size);

    // Заполнение массива случайными числами
    for (size_t i = 0; i < arr->size; i++) {
        array_set(arr, i, rand() % 100); // Заполняем случайными числами от 0 до 99
    }

    printArray(*arr, "Исходный массив");

    std::cout << "Введите значения m и n: ";
    std::cin >> m >> n;

    processArray(*arr, m, n);
    printArray(*arr, "Обработанный массив");

    findMaxSum(*arr);

    array_delete(arr);

    return 0;
}
