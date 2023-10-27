#include "array.h"
#include <iostream>

using namespace std;

int task1(Array* arr) {

    size_t size = array_size(arr);
    int maxLength = 0;
    int currentLength = 0;

    for (int i = 0; i < size; i++) {
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
    return maxLength;
}


void task2(Array* arr) {
    for (int i = 0; i < size; i++) {
        int n = 0;
        for (int j = 0; j < size; j++) {
            if (array_get(arr, i) != array_get(arr, j)) {
                n++;
            }
        }
        if (n == size - 1) {
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
