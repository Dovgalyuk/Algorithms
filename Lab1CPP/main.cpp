#include <iostream>
#include <random>
#include <map>
#include <algorithm>
#include "LibraryCPP/array.h"

// нахождение максимального элемента среди элементов с четными индексами
int findMaxEvenIndex(const Array<int>& arr) {
    if (arr.size() == 0) {
        throw std::invalid_argument("Array is empty");
    }

    int maxVal = arr.at(0);

    for (size_t i = 2; i < arr.size(); i += 2) {
        if (arr.at(i) > maxVal) {
            maxVal = arr.at(i);
        }
    }

    return maxVal;
}

// определение числа, которое встречается чаще всего
int findMostFrequent(const Array<int>& arr) {
    if (arr.size() == 0) {
        throw std::invalid_argument("Array is empty");
    }

    std::map<int, int> counts;
    for (size_t i = 0; i < arr.size(); ++i) {
        counts[arr.at(i)]++;
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
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);

    size_t size1;
    std::cout << "Введите размер массива для поиска максимума среди четных индексов: ";
    std::cin >> size1;

    if (size1 <= 0) {
        std::cerr << "Размер массива должен быть положительным." << std::endl;
        return 1;
    }

    Array<int> arr1(size1);
    for (size_t i = 0; i < size1; ++i) {
        arr1[i] = distrib(gen);
        std::cout << arr1[i] << " ";
    }
    std::cout << std::endl;

    try {
        int maxEven = findMaxEvenIndex(arr1);
        std::cout << "Максимальный элемент среди элементов с четными индексами: " << maxEven << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    size_t size2;
    std::cout << "Введите размер массива для поиска наиболее часто встречающегося элемента: ";
    std::cin >> size2;

    if (size2 <= 0) {
        std::cerr << "Размер массива должен быть положительным." << std::endl;
        return 1;
    }

    Array<int> arr2(size2);
    for (size_t i = 0; i < size2; ++i) {
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
