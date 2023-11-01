#include "array.h"
#include <iostream>

using namespace std;

void task1(Array* arr) {

    size_t size = array_size(arr);
    size_t maxLength = 0;
    size_t currentLength = 0;

    for (size_t i = 0; i < size; i++) {
        if (array_get(arr, i) % 2 == 1)
            currentLength++;
        else {
            if (currentLength > maxLength) {
                maxLength = currentLength;
            }
            currentLength = 0;
        }
    }
    if (currentLength > maxLength)
        maxLength = currentLength;
    cout << "Result: " << maxLength;
}


void task2(Array* arr) {
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; i++) {
        size_t n = 0;
        for (size_t j = 0; j < size; j++) {
            if (array_get(arr, i) == array_get(arr, j)) {
                n++;
            }
        }
        if (n == 1) {
            cout << array_get(arr, i) << " ";
        }
    }
}

void CreateArray(Array* arr) {
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; i++)
        array_set(arr, i, rand());
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
}
