
// main.cpp
#include "array.h"
#include <iostream>
#include <ctime>

void processArray(Array* arr, int m, int n) {
    for (size_t i = 0; i < array_size(arr); i++) {
        if (array_get(arr, i) % 2 != 0) {
            array_set(arr, i, array_get(arr, i) - m);
        }
        if (i % 2 == 0) {
            array_set(arr, i, array_get(arr, i) + n);
        }
    }
}

void findMaxSum(const Array* arr) {
    if (array_size(arr) < 5) {
        std::cout << "Массив слишком мал для вычисления максимальной суммы пяти соседних элементов." << std::endl;
        return;
    }

    int currentSum = 0;

    // Вычисляем начальную сумму первых пяти элементов
    for (size_t i = 0; i < 5; i++) {
        currentSum += array_get(arr, i);
    }

    int maxSum = currentSum;

    // Проходимся по массиву, обновляя сумму на каждой итерации
    for (size_t i = 5; i < array_size(arr); i++) {
        // Добавляем новый элемент
        currentSum += array_get(arr, i);
        // Удаляем самый старый элемент (те, что за пределами "скользящего окна")
        currentSum -= array_get(arr, i - 5);

        // Обновляем максимальную сумму при необходимости
        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
    }

    std::cout << "Максимальная сумма пяти соседних элементов: " << maxSum << std::endl;
}


void printArray(const Array* arr, const std::string& label) {
    std::cout << label << ": ";
    for (size_t i = 0; i < array_size(arr); i++) {
        std::cout << array_get(arr, i) << " ";
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
    for (size_t i = 0; i < array_size(arr); i++) {
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