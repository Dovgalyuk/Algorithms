#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

Array* array_create_and_read(ifstream &input) {
    int n;
    input >> n;
    Array* arr = array_create(n);
    for (int i = 0; i < n; ++i) {
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array* arr) {
    size_t n = array_size(arr);
    if (n == 0) return;

    int min = array_get(arr, 0), max = array_get(arr, 0);
    for (size_t i = 1; i < n; ++i) {
        int value = array_get(arr, i);
        if (value < min) min = value;
        if (value > max) max = value;
    }

    double avg = (min + max) / 2.0;
    for (size_t i = 0; i < n; ++i) {
        if (array_get(arr, i) > avg) {
            cout << i <<  " ";
        }
    }
    cout << endl;
}

void task2(Array* arr) {
    size_t n = array_size(arr);
    if (n == 0) return;
  
    size_t min_index = 0, max_index = 0;
    for (size_t i = 1; i < n; ++i) {
        if (array_get(arr, i) < array_get(arr, min_index)) min_index = i;
        if (array_get(arr, i) > array_get(arr, max_index)) max_index = i;
    }

    if (min_index > max_index) {
        swap(min_index, max_index);
    }

    int sum = 0;
    for (size_t i = min_index + 1; i < max_index; ++i) {
        sum += array_get(arr, i);
    }
    cout << sum << endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input) {
        cerr << "Ошибка открытия файла" << endl;
        return 1;
    }

    Array* arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    input.close();
    return 0;
}
