#include "array.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

// Функция для создания массива и заполнения его случайными числами
Array array_create_and_fill_random(size_t n) {
    Array arr(n);
    for (size_t i = 0; i < n; ++i) {
        arr.set(i, rand() % 100 - 50); // случайные числа от -50 до 49
    }
    return arr;
}

// Task 1: Сумма чётных положительных элементов массива
int task1(const Array &arr) {
    int sum = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        int value = arr.get(i);
        if (value > 0 && value % 2 == 0) {
            sum += value;
        }
    }
    return sum;
}

// Task 2: Элементы, которые не делятся на другие элементы массива
vector<int> task2(const Array &arr) {
    vector<int> nonDivisibleElements;
    for (size_t i = 0; i < arr.size(); ++i) {
        int value = arr.get(i);
        bool divisible = false;

        for (size_t j = 0; j < arr.size(); ++j) {
            if (i != j && arr.get(j) != 0 && value % arr.get(j) == 0) {
                divisible = true;
                break;
            }
        }

        if (!divisible) {
            nonDivisibleElements.push_back(value);
        }
    }
    return nonDivisibleElements;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    if (!input.is_open() || !output.is_open()) {
        cerr << "Error opening input or output file!" << endl;
        return 1;
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    size_t n;

    //Task 1
    input >> n;
    Array arr1 = array_create_and_fill_random(n);
    output << "Original array for Task 1: ";
    for (size_t i = 0; i < arr1.size(); ++i) {
        output << arr1.get(i) << " ";
    }
    output << endl;

    int sum = task1(arr1);
    output << "Sum of even positive elements: " << sum << endl;

    //Task 2
    input >> n;
    Array arr2 = array_create_and_fill_random(n);
    output << "Original array for Task 2: ";
    for (size_t i = 0; i < arr2.size(); ++i) {
        output << arr2.get(i) << " ";
    }
    output << endl;

    vector<int> nonDivisibleElements = task2(arr2);
    output << "Elements that are not divisible by any other element: ";
    if (nonDivisibleElements.empty()) {
        output << "None found." << endl;
    } else {
        for (int element : nonDivisibleElements) {
            output << element << " ";
        }
        output << endl;
    }

    input.close();
    output.close();

    return 0;
}
