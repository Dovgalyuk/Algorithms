#include <iostream>
#include <ctime>
#include "array.h"

using namespace std;
void summapos(const Array* arr) {
    cout << "Massiv:";
    for (size_t k = 0; k < array_size(arr); k++) {
        cout << array_get(arr, k) << " ";
    }
    cout << endl;

    int sum = 0;
    for (size_t k = 0; k < array_size(arr); k++) {
        if (array_get(arr, k) > 0 && array_get(arr, k) % 2 == 0) {
            sum += array_get(arr, k);
        }
    }

    cout << "Summaa (1 zadanie):" << sum << endl;
}

void nedel(const Array* arr) {
    cout << "Massiv:" << " ";
    for (size_t k = 0; k < array_size(arr); k++) {
        cout << array_get(arr, k) << " ";
    }
    cout << endl;
    cout << "nedel:" << " ";
    for (size_t i = 0; i < array_size(arr); ++i) {
        bool digit = false;
        for (size_t j = 0; j < array_size(arr); ++j) {
            if (array_get(arr, j) != 0 && array_get(arr, i) % array_get(arr, j) == 0 && i != j) {
                digit = true;
                break;
            }
        }
        if (!digit) {
            cout << array_get(arr, i) << " ";
        }
    }
}

int main() {
    cout << "Input array: ";
    size_t size;
    cin >> size;
    Array* mas = array_create(size);
    srand(time(0));
    for (size_t i = 0; i < size; i++) {
        array_set(mas, i, rand() % 100);
    }
    cout << std::endl;
    summapos(mas);
    nedel(mas);
    array_delete(mas);
    return 0;
}