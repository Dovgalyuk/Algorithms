#include <iostream>
#include <random>
#include <algorithm>
#include <map>
#include <stdexcept>

#include "Array.h"

// нахождение максимального элемента среди элементов с четными индексами
int findMaxEvenIndex(const Array<int>& arr) {
    if (arr.getSize() == 0) {
        throw std::runtime_error("Массив пуст!");
    }

    int maxVal = arr[0];

    for (size_t i = 2; i < arr.getSize(); i += 2) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    return maxVal;
}

// определение числа, которое встречается чаще всего
int findMostFrequent(const Array<int>& arr) {
    if (arr.getSize() == 0) {
        throw std::runtime_error("Массив пуст!");
    }

    std::map<int, int> counts;
    for (size_t i = 0; i < arr.getSize(); ++i) {
        counts[arr[i]]++;
    }

    int mostFrequent = arr[0];
    int maxCount = counts[arr[0]];

    for (const auto& pair : counts) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostFrequent = pair.first;
        }
    }

    return mostFrequent;
}

int main() {
	setlocale(LC_ALL, "Russian");
    int size1, size2;

    std::cout << "Введите размер массива для поиска максимума среди четных индексов: ";
    std::cin >> size1;

    if (size1 <= 0) {
        std::cerr << "Размер массива должен быть положительным." << std::endl;
        return 1;
    }

    Array<int> arr1(size1);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100); // генерация чисел от 1 до 100

    for (size_t i = 0; i < arr1.getSize(); ++i) {
        arr1.set(i, distrib(gen));
        std::cout << arr1.get(i) << " ";
    }
    std::cout << std::endl;

    try {
        int maxEven = findMaxEvenIndex(arr1);
        std::cout << "Максимальный элемент среди элементов с четными индексами: " << maxEven << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Введите размер массива для поиска наиболее часто встречающегося элемента: ";
    std::cin >> size2;

    if (size2 <= 0) {
        std::cerr << "Размер массива должен быть положительным." << std::endl;
        return 1;
    }

    Array<int> arr2(size2);
    for (size_t i = 0; i < arr2.getSize(); ++i) {
        arr2[i] = distrib(gen);
        std::cout << arr2[i] << " ";
    }
    std::cout << std::endl;

    try {
        int mostFrequent = findMostFrequent(arr2);
        std::cout << "Наиболее часто встречающийся элемент: " << mostFrequent << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
