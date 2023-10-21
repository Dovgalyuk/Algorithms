#include "array.h"
#include <iostream>
#include <cstdlib>
using namespace std;

    void FillRandom(Array* arr) {
        size_t size = array_size(arr);
        for (size_t i = 0; i < size; i++) {
            array_set(arr, i,static_cast<int>(rand() % (250 - 100 + 1) + 100));
        }
    }
    void MinMax(Array* arr) {
        int fix = 0;

        int max = array_get(arr, 0);
        int max1 = 0;
        int max2 = 0;

        for (size_t i = 0; i < array_size(arr); i++) {
            if (array_get(arr, i) > max) {
                max = array_get(arr, i);
            }
        }

        for (size_t i = 0; i < array_size(arr); i++) {
            if (array_get(arr, i) == max && fix == 0) {
                max1 = i;
                fix += 1;
            }
            else if (array_get(arr, i) == max && fix == 1) {
                max2 = i;
                fix += 1;
                break;
            }
        }
        if (max2 != 0) {
            cout << max1 << " " << max2 << endl;
            }
            else {
                cout << max << endl;
            }
        }
    void Sort(Array* arr) {
        int peregon = 0;
        for (size_t i = 0; i < array_size(arr) - 1; i++) {
            for (size_t j = i + 1; j < array_size(arr); j++) {
                if (array_get(arr,j) < array_get(arr, i)) {
                    peregon = array_get(arr, i);
                    array_set(arr, i, static_cast<int>(array_get(arr, j)));
                    array_set(arr, j,static_cast<int>(peregon));
                }
            }
        }
    }
    int Difference(Array* arr) {
        Sort(arr);
        int min = 1000000;
        Array* carChet = NULL;
        for (size_t i = 0; i < array_size(arr); i++) {
            if (array_get(arr,i) % 2 == 0) {
                carChet = array_create(1);
                array_set(carChet,0,static_cast<int>(array_get(arr,i)));
                break;
            }
        }
        for (size_t i = 0; i < array_size(arr); i++) {
            if (array_get(arr, i) % 2 == 0) {
                carChet = re_size(carChet, static_cast<int>(array_get(arr, i)));
            }
        }
        for (size_t i = 1; i < array_size(carChet); i++) {
            if (array_get(carChet,i) - array_get(carChet,i-1) < min && array_get(carChet,i) != array_get(carChet,i-1)) {
                min = array_get(carChet,i) - array_get(carChet,i-1);
            }
        }
        return min;
    }
    int main() {
        setlocale(LC_ALL, "Russian");
        Array* arr = NULL;
        size_t size;

        cout << "Введите кол-во автомобилей: ";
        cin >> size;
        arr = array_create(size);
        FillRandom(arr);
        cout << "Минимальный и максимальный элемент: ";
        MinMax(arr);
        cout << "Минимальная разница между скоростями автомобилей: "<<Difference(arr);
    }
