#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "array.h"

using namespace std;

// Функция для вычисления среднего арифметического положительных и отрицательных чисел
void task1(Array* arr) {
    for (size_t i = 0; i < array_size(arr); i++) { // случайная инициализация массива
        array_set(arr, i, rand());
    }

    size_t posCount = 0, negCount = 0;
    int posSum = 0, negSum = 0;
    cout << "Array: ";
    for (size_t i = 0; i < array_size(arr); i++) {
        int num = array_get(arr, i);
        cout << num << " ";
        if (num > 0) {
            posSum += num;
            posCount++;
        } else if (num < 0) {
            negSum += num;
            negCount++;
        }
    }

    cout << endl;

    if (posCount > 0)
        cout << "Arithmetic mean of positive numbers: " << static_cast<double>(posSum) / posCount << endl;
    else
        cout << "There are no positive numbers in the array." << endl;

    if (negCount > 0)
        cout << "Arithmetic mean of negative numbers: " << static_cast<double>(negSum) / negCount << endl;
    else
        cout << "There are no negative numbers in the array." << endl;
}

// Функция для нахождения минимальной разницы между четными числами в массиве
void task2(Array* arr) {
    for (size_t i = 0; i < array_size(arr); i++) {
        array_set(arr, i, rand() % 202 - 101); // создайте массив со значениями от -101 до 101
    }

    cout << "Array: ";
    for (size_t i = 0; i < array_size(arr); i++) {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;

    Array* evenArr = array_create(array_size(arr));
    size_t evenCount = 0;

   // Добавляйте в новый массив только четные элементы
    for (size_t i = 0; i < array_size(arr); i++) {
        if (array_get(arr, i) % 2 == 0) {
            array_set(evenArr, evenCount++, array_get(arr, i));
        }
    }

    if (evenCount < 2) {
        cout << "Not enough even elements." << endl;
        array_delete(evenArr);
        return;
    }

    int minDiff = abs(array_get(evenArr, 0) - array_get(evenArr, 1));

    //Найдите минимальную разницу между различными четными элементами
    for (size_t i = 0; i < evenCount - 1; i++) {
        for (size_t j = i + 1; j < evenCount; j++) {
            int diff = abs(array_get(evenArr, i) - array_get(evenArr, j));
            if (diff < minDiff) {
                minDiff = diff;
            }
        }
    }

    cout << "Minimum difference between even numbers: " << minDiff << endl;

    array_delete(evenArr);
}

int main(int argc, char* argv[]) {
    srand(static_cast<unsigned>(time(NULL)));

    Array* arr = nullptr;

    // Размер входных данных для задач 1 и 2
    istream* input = &cin;
    ifstream inputFile;
    size_t arraySize;
    size_t arraySize2;

    cout << "Enter array size for task 1 and 2: " << std::endl;

    if (argc >= 1) {
        inputFile.open(argv[1]);
        if (!inputFile) {
            std::cerr << "Error: file not found:" << argv[1] << std::endl;
            return 1;
        }
        input = &inputFile;
    }

    if (!(*input >> arraySize >> arraySize2)) {
        std::cerr << "Error: Incorrect data entry. Enter the size of the array.";
        return 1;
    }

    if (arraySize == 0) {
        std::cerr << "Error: The size of the array cannot be zero." << std::endl;
        return 1;
    }

    arr = array_create(arraySize);
    task1(arr);


    // Размер входных данных для задачи 2
    cout << "Enter array size for task 2: ";

    arr = array_create(arraySize2);
    task2(arr);
    array_delete(arr);

    return 0;
}
