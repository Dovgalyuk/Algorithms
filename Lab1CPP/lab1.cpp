#include "array.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;



void task1(Array* arr) {
    if (arr->size == 0) return;

    array_set(arr, 0, 0); 
    if (arr->size > 1) {
        array_set(arr, 1, 1); 
    }

    for (size_t i = 2; i < arr->size; ++i) {
        array_set(arr, i, array_get(arr, i - 1) + array_get(arr, i - 2));
    }
}


Array* task2(Array* arr) {
    Array* result = array_create(arr->size);
    size_t result_index = 0;

    for (size_t i = 0; i < arr->size; ++i) {
        bool is_divisible = false;
        for (size_t j = 0; j < arr->size; ++j) {
            if (i != j && array_get(arr, i) % array_get(arr, j) == 0) {
                is_divisible = true;
                break;
            }
        }
        if (!is_divisible) {
            array_set(result, result_index++, array_get(arr, i));
        }
    }

    // Resize the result array to fit the actual number of elements
    Array* resized_result = array_create(result_index);
    for (size_t i = 0; i < result_index; ++i) {
        array_set(resized_result, i, array_get(result, i));
    }
    array_delete(result);
    return resized_result;
}


int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
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

    // Числа Фибоначчи
    size_t fib_size;
    cout << "Введите размер массива Фибоначчи: ";
    if (!(*input >> fib_size)) {
        cerr << "Ошибка: некорректный ввод данных для размера массива Фибоначчи" << endl;
        return 1;
    }

    Array* fib_array = array_create(fib_size);
    task1(fib_array);

    cout << "Массив Фибоначчи: ";
    for (size_t i = 0; i < array_size(fib_array); ++i) {
        cout << array_get(fib_array, i) << " ";
    }
    cout << endl;

    array_delete(fib_array);

    // Массив рандомных чисел
    size_t rand_size;
    cout << "Введите размер случайного массива: ";
    if (!(*input >> rand_size)) {
        cerr << "Ошибка: некорректный ввод данных для размера случайного массива" << endl;
        return 1;
    }

    Array* rand_array = array_create(rand_size);
    srand(static_cast<unsigned>(time(0)));

    for (size_t i = 0; i < rand_size; ++i) {
        array_set(rand_array, i, rand() % 100 + 1); 
    }

    cout << "Случайный массив: ";
    for (size_t i = 0; i < array_size(rand_array); ++i) {
        cout << array_get(rand_array, i) << " ";
    }
    cout << endl;

    Array* non_divisible_array = task2(rand_array);

    cout << "Несоразмерные элементы: ";
    for (size_t i = 0; i < array_size(non_divisible_array); ++i) {
        cout << array_get(non_divisible_array, i) << " ";
    }
    cout << endl;

    array_delete(rand_array);
    array_delete(non_divisible_array);

    if (inputFile.is_open()) {
        inputFile.close(); 
    }

    return 0;
}