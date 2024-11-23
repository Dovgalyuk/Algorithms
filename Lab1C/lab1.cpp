#include <iostream>
#include <fstream>
#include "array.h"
using namespace std;

void printTwoDigitNumbers(Array *array);
void printThreeDigitNumbers(Array *array);
int sumBetweenMinAndMax(Array *array);

int main() {
    string filename;
    filename = "input.txt";

    ifstream file(filename);
    if (!file) {
        cout << "Ошибка: файл не найден!" << endl;
        return 1;
    }

    size_t size;
    file >> size;

    if (size <= 0) {
        cout << "Ошибка: размер массива должен быть положительным!" << endl;
        return 1;
    }

    Array *array = array_create(size, NULL);
    int value;

    for (size_t i = 0; i < array_size(array); i++) {
        if (file >> value) {
            array_set(array, i, (Data)(intptr_t)value);
        } else {
            cout << "Ошибка: недостаточно данных в файле!" << endl;
            array_delete(array);
            return 1;
        }
    }
    file.close();

    cout << "Двузначные числа: ";
    printTwoDigitNumbers(array);
    cout << endl;

    cout << "Трёхзначные числа: ";
    printThreeDigitNumbers(array);
    cout << endl;

    cout << "Сумма между минимальным и максимальным: ";
    cout << sumBetweenMinAndMax(array) << endl;

    array_delete(array);
    return 0;
}


void printTwoDigitNumbers(Array *array) {
    for (size_t i = 0; i < array_size(array); i++) {
        int num = (int)(intptr_t)array_get(array, i);
        if (abs(num) >= 10 && abs(num) <= 99) {
            cout << num << " ";
        }
    }
}

void printThreeDigitNumbers(Array *array) {
    for (size_t i = 0; i < array_size(array); i++) {
        int num = (int)(intptr_t)array_get(array, i);
        if (abs(num) >= 100 && abs(num) <= 999) {
            cout << num << " ";
        }
    }
}

int sumBetweenMinAndMax(Array *array) {
    size_t minIndex = 0, maxIndex = 0;
    for (size_t i = 1; i < array_size(array); i++) {
        int num = (int)(intptr_t)array_get(array, i);
        if (num < (int)(intptr_t)array_get(array, minIndex)) {
            minIndex = i;
        }
        if (num > (int)(intptr_t)array_get(array, maxIndex)) {
            maxIndex = i;
        }
    }

    if (abs((int)(minIndex - maxIndex)) <= 1) {
        return 0;
    }

    int sum = 0;
    if (minIndex < maxIndex) {
        for (size_t i = minIndex + 1; i < maxIndex; i++) {
            sum += (int)(intptr_t)array_get(array, i);
        }
    } else {
        for (size_t i = maxIndex + 1; i < minIndex; i++) {
            sum += (int)(intptr_t)array_get(array, i);
        }
    }
    return sum;
}
