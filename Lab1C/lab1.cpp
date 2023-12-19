#include <iostream>
#include <ctime>
#include "array.h"
#include <climits>

using namespace std;

void task1(Array* arr) {
    size_t size = array_size(arr);
    cout << "All elements: ";
    for (size_t i = 0; i < size; i++) {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;

    cout << "Two-digit numbers: ";
    for (size_t i = 0; i < size; i++) {
        if (array_get(arr, i) >= 10 && array_get(arr, i) <= 99) {
            cout << array_get(arr, i) << " ";
        }
    }
    cout << endl;

    cout << "Three-digit numbers: ";
    for (size_t i = 0; i < size; i++) {
        if (array_get(arr, i) >= 100 && array_get(arr, i) <= 999) {
            cout << array_get(arr, i) << " ";
        }
    }
    cout << endl;
}
void task2(Array* arr) {
    size_t minDiff = INT_MAX;
    size_t size = array_size(arr);

    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (array_get(arr, i) % 2 == 0 && array_get(arr, j) % 2 == 0) {
                size_t diff = abs(array_get(arr, i) - array_get(arr, j));
                if (diff < minDiff) {
                    minDiff = diff;
                }
            }
        }
    }

    if (minDiff == INT_MAX) {
        cout << "There are no two different even elements in the array.\n";
    }
    else {
        cout << "The minimum difference between different even elements: " << minDiff << endl;
    }
}
void CreateArray(Array* arr) {
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; i++)
        array_set(arr, i, 1 + rand() % 1000);
}

int main() {
    srand((unsigned int)time(NULL));
    Array* arr = NULL;
    size_t size;

    cin >> size;
    arr = array_create(size);
    CreateArray(arr);
    task1(arr);
    array_delete(arr);

    cin >> size;
    arr = array_create(size);
    CreateArray(arr);
    task2(arr);
    array_delete(arr);
    return 0;
}
