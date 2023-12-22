#include <iostream>
#include <cstdlib>
#include <ctime>
#include "array.h"
#include "array.cpp"
using namespace std;

void fillArrayWithRandomNumbers(Array* arr) {
    srand(time(0));
    for (size_t i = 0; i < array_size(arr); i++) {
        array_set(arr, i, rand() % 100 - 50);
    }
}
void printArray(const Array* arr) {
    cout << "Массив: ";
    for (size_t i = 0; i < array_size(arr); i++) {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;
}
void task1(Array* arr, int k1, int k2) {
    for (size_t i = 0; i < array_size(arr); i++) {
        int num = array_get(arr, i);
        if (num > 0) {
            array_set(arr, i, num - k1); // Вычитаем k1 из положительных элементов
        }
        else if (num < 0) {
            array_set(arr, i, num - k2); // Вычитаем k2 из отрицательных элементов
        }
    }
    printArray(arr);
}

void task2(Array* arr) {
    cout << "Уникальные элементы: ";
    for (size_t i = 0; i < array_size(arr); i++) {
        bool isUnique = true;
        for (size_t j = 0; j < array_size(arr); j++) {
            if (i != j && array_get(arr, i) == array_get(arr, j)) {
                isUnique = false;
                break;
            }
        }
        if (isUnique) {
            cout << array_get(arr, i) << " ";
        }
    }
    cout << endl;

    cout << "Массив: ";
    for (size_t i = 0; i < array_size(arr); i++) {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    size_t size;
    cout << "Введите размер массива: ";
    cin >> size;

    Array* arr = array_create(size);
    fillArrayWithRandomNumbers(arr);
    printArray(arr);

    int k1, k2;
    cout << "Введите k1: ";
    cin >> k1;
    cout << "Введите k2: ";
    cin >> k2;

    task1(arr, k1, k2);

    task2(arr);

    array_delete(arr);

    return 0;
}
