#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

// Функция 1: Разделение на положительные и отрицательные
void separatePositiveNegative(Array* source, Array* positive, Array* negative, 
                             size_t* pos_count, size_t* neg_count) {
    *pos_count = 0;
    *neg_count = 0;
    
    for (size_t i = 0; i < array_size(source); ++i) {
        int value = array_get(source, i);
        if (value > 0) {
            array_set(positive, (*pos_count)++, value);
        } else if (value < 0) {
            array_set(negative, (*neg_count)++, value);
        }
    }
}

// Функция 2: Поиск уникальных элементов - использовать Array вместо vector
void findUniqueElements(Array* source, Array* unique, size_t* unique_count) {
    *unique_count = 0;
    
    for (size_t i = 0; i < array_size(source); ++i) {
        int value = array_get(source, i);
        int count = 0;
        for (size_t j = 0; j < array_size(source); ++j) {
            if (array_get(source, j) == value) {
                count++;
            }
        }
        if (count == 1) {
            array_set(unique, (*unique_count)++, value);
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
    
    // Создаем массивы для результатов (максимальный размер = исходный размер)
    Array* positive = array_create(size);
    Array* negative = array_create(size);
    Array* unique = array_create(size);
    
    size_t pos_count, neg_count, unique_count;
    
    separatePositiveNegative(arr, positive, negative, &pos_count, &neg_count);
    findUniqueElements(arr, unique, &unique_count);
    
    cout << "Positive numbers: ";
    for (size_t i = 0; i < pos_count; ++i) {
        cout << array_get(positive, i) << " ";
    }
    cout << endl;
    
    cout << "Negative numbers: ";
    for (size_t i = 0; i < neg_count; ++i) {
        cout << array_get(negative, i) << " ";
    }
    cout << endl;
    
    cout << "Unique elements: ";
    for (size_t i = 0; i < unique_count; ++i) {
        cout << array_get(unique, i) << " ";
    }
    cout << endl;
    
    array_delete(arr);
    array_delete(positive);
    array_delete(negative);
    array_delete(unique);
    return 0;
}