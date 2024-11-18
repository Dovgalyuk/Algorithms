#include <fstream>
#include <iostream>

#include "array.h"

Array* readFile(const std::string& filename) {
    std::ifstream input(filename);
    int size;

    if (input >> size) {
        Array* arr = array_create(size);
        for (int i = 0; i < size; ++i) {
            Data value;
            input >> value;
            array_set(arr, i, value);
        }
        return arr;
    }

    return nullptr; // если не читается размер
}

void task1(const std::string& input) {
    Array* heights = readFile(input);
    if (heights == nullptr || array_size(heights) == 0) {
        std::cout << "array empty." << std::endl;
        return;
    }

    double sum = 0;
    size_t size = array_size(heights);
    for (size_t i = 0; i < size; ++i) {
        sum += array_get(heights, i);
    }
    double avg = sum / size;

    int count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (array_get(heights, i) > avg) {
            count++;
        }
    }

    std::cout << "numb of highest then avg: " << count << std::endl;

    array_delete(heights);
}

void task2(const std::string& input) {
    Array* arr = readFile(input);
    if (arr == nullptr || array_size(arr) == 0) {
        std::cout << "array is empty" << std::endl;
        return;
    }

    Array* notDivide = array_create(array_size(arr)); // не делящихся элементов не больше размера исх. массива
    size_t notDivideCount = 0;

    size_t size = array_size(arr);
    for (size_t i = 0; i < size; ++i) {
        bool isDivide = false;
        for (size_t j = 0; j < size; ++j) {
            if (i != j && array_get(arr, i) % array_get(arr, j) == 0) {
                isDivide = true;
                break;
            }
        }
        if (!isDivide) {
            array_set(notDivide, notDivideCount++, array_get(arr, i));
        }
    }

    std::cout << "not devide by others: ";
    for (size_t i = 0; i < notDivideCount; ++i) {
        std::cout << array_get(notDivide, i) << " ";
    }
    std::cout << std::endl;

    array_delete(arr);        
    array_delete(notDivide);  
}

int main() {
    const std::string file = "input.txt";

    task1(file);
    task2(file);

    return 0;
}