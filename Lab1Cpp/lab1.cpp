#include <iostream>
#include <fstream>
#include <vector>
#include "../LibraryCPP/array.h"  // Подключаем готовый header

using namespace std;

// Функция 1: Разделение на положительные и отрицательные
void separatePositiveNegative(Array* source, vector<int>& positive, vector<int>& negative) {
    for (size_t i = 0; i < array_size(source); ++i) {
        int value = array_get(source, i);
        if (value > 0) {
            positive.push_back(value);
        } else if (value < 0) {
            negative.push_back(value);
        }
    }
}

// Функция 2: Поиск уникальных элементов
void findUniqueElements(Array* source, vector<int>& unique) {
    for (size_t i = 0; i < array_size(source); ++i) {
        int value = array_get(source, i);
        int count = 0;
        for (size_t j = 0; j < array_size(source); ++j) {
            if (array_get(source, j) == value) {
                count++;
            }
        }
        if (count == 1) {
            unique.push_back(value);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }
    
    int size;
    inputFile >> size;
    
    // Используем готовые функции из LibraryCPP
    Array* arr = array_create(size);
    
    for (int i = 0; i < size; ++i) {
        int value;
        inputFile >> value;
        array_set(arr, i, value);
    }
    inputFile.close();
    
    cout << "Original array: ";
    for (int i = 0; i < size; ++i) {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;
    
    vector<int> positive, negative;
    separatePositiveNegative(arr, positive, negative);
    
    cout << "Positive numbers: ";
    for (int num : positive) {
        cout << num << " ";
    }
    cout << endl;
    
    cout << "Negative numbers: ";
    for (int num : negative) {
        cout << num << " ";
    }
    cout << endl;
    
    vector<int> unique;
    findUniqueElements(arr, unique);
    
    cout << "Unique elements: ";
    for (int num : unique) {
        cout << num << " ";
    }
    cout << endl;
    
    array_delete(arr);
    return 0;
}