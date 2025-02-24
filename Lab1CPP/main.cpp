#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include "array.h"

using namespace std;

// Функция для нахождения суммы элементов, не превышающих 20
int sum_elements_not_exceeding(Array* arr, int limit) {
    int sum = 0;
    for (size_t i = 0; i < array_size(arr); ++i) {
        if (array_get(arr, i) <= limit) {
            sum += array_get(arr, i);
        }
    }
    return sum;
}

// Функция для поиска наиболее часто встречающегося числа
int most_frequent_element(Array* arr) {
    unordered_map<int, int> frequency;
    
    for (size_t i = 0; i < array_size(arr); ++i) {
        frequency[array_get(arr, i)]++;
    }

    int max_count = 0;
    int most_frequent = array_get(arr, 0);

    for (const auto& pair : frequency) {
        if (pair.second > max_count) {
            max_count = pair.second;
            most_frequent = pair.first;
        }
    }

    return most_frequent;
}

int main(int argc, char* argv[]) {
    istream* input = &cin;
    ifstream inputFile;

    if (argc >= 2) {
        inputFile.open(argv[1]);
        if (!inputFile) {
            cerr << "Ошибка: не удалось открыть файл " << argv[1] << endl;
            return 1;
        }
        input = &inputFile;
    }

    size_t size1, size2;
    
    if (!(*input >> size1)) {
        cerr << "Ошибка: некорректный ввод данных" << endl;
        return 1;
    }

    Array* arr1 = array_create(size1);
    for (size_t i = 0; i < size1; ++i) {
        int value;
        if (!(*input >> value)) value = rand() % 50; 
        array_set(arr1, i, value);
    }

    cout << "Массив: ";
    for (size_t i = 0; i < array_size(arr1); ++i) {
        cout << array_get(arr1, i) << " ";
    }
    cout << endl;

    cout << "Сумма элементов (<=20): " << sum_elements_not_exceeding(arr1, 20) << endl;
    array_delete(arr1);

    if (!(*input >> size2)) {
        cerr << "Ошибка: некорректный ввод данных" << endl;
        return 1;
    }

    Array* arr2 = array_create(size2);
    for (size_t i = 0; i < size2; ++i) {
        int value;
        if (!(*input >> value)) value = rand() % 50;
        array_set(arr2, i, value);
    }

    cout << "Массив: ";
    for (size_t i = 0; i < array_size(arr2); ++i) {
        cout << array_get(arr2, i) << " ";
    }
    cout << endl;

    cout << "Наиболее часто встречающееся число: " << most_frequent_element(arr2) << endl;
    array_delete(arr2);

    if (inputFile.is_open()) {
        inputFile.close();
    }

    return 0;
}