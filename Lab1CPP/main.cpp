#include "array.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

// Функция вычисления факториала.

Data factorial(int n) {
    Data result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Первая задача: заполнение массива факториалами
void process_factorials(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open " + filename);
    }
    
    int size;
    file >> size;
    if (size < 0) {
        throw std::invalid_argument("Negative array size");
    }
    
    Array* arr = array_create(size);
    for (int i = 0; i < size; ++i) {
        array_set(arr, i, factorial(i));
    }
    
    std::cout << "Factorial array: ";
    for (int i = 0; i < size; ++i) {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << std::endl;
    
    array_delete(arr);
}

// Вторая задача: поиск элементов, встречающихся ровно два раза
void process_duplicates(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open " + filename);
    }
    
    int size;
    file >> size;
    
    // Пропускаем первое число (размер для факториалов)
    int factorial_size;
    file >> factorial_size;
    
    Array* arr = array_create(factorial_size);
    
    for (int i = 0; i < factorial_size; ++i) {
        Data value;
        if (!(file >> value)) {
            throw std::runtime_error("Not enough data in " + filename);
        }
        array_set(arr, i, value);
    }
    
    std::map<Data, int> count;
    for (int i = 0; i < factorial_size; ++i) {
        count[array_get(arr, i)]++;
    }
    
    std::vector<Data> result;
    for (const auto& pair : count) {
        if (pair.second == 2) {
            result.push_back(pair.first);
        }
    }
    
    std::cout << "Elements appearing twice: ";
    for (Data val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    array_delete(arr);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }
    
    std::string input_file = argv[1];
    
    try {
        process_factorials(input_file);
        process_duplicates(input_file);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}