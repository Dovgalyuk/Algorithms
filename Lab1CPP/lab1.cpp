#include <iostream>
#include <fstream>
#include <unordered_map>
#include "array.h"


Array* array_create_and_read(std::ifstream& input) {
    size_t n;
    input >> n;
    Data x;
    Array* arr = array_create(n); 

    
    for (size_t i = 0; i < n; ++i) {
        input >> x;
        array_set(arr, i, x);
    }

    return arr; 
}


void task1(std::ifstream& input) {
    Array* arr = array_create_and_read(input);

    
    int sum = 0;
    for (size_t i = 0; i < array_size(arr); ++i) {
        int value = array_get(arr, i);
        if (value > 0 && value % 2 == 0) {
            sum += value;
        }
    }

    std::cout << "sum of even positive elements: " << sum << std::endl;

    array_delete(arr); 
}


void task2(std::ifstream& input) {
    Array* arr = array_create_and_read(input);

    std::unordered_map<int, int> freq;

    for (size_t i = 0; i < array_size(arr); ++i) {
        int value = array_get(arr, i);
        freq[value]++;
    }

    std::cout << "Elements that occur exactly twice: ";
    bool found = false;
    for (const auto& pair : freq) {
        if (pair.second == 2) {
            std::cout << pair.first << " ";
            found = true;
        }
    }

    if (!found) {
        std::cout << "Нет элементов, которые встречаются ровно два раза." << std::endl;
    }
    else {
        std::cout << std::endl;
    }

    array_delete(arr); 
}

int main() {
   
    std::ifstream input("input.txt");
    if (input.is_open()) {
        task1(input);

        input.clear();
        input.seekg(0);

        task2(input);

       
    }
    input.close();
    return 0;
}