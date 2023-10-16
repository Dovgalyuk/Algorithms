#include "array.h"
#include <iostream>
#include <cstdlib>
using namespace std;

    void FillRandom(Array* arr) {
        size_t size = array_size(arr);
        for (int i = 0; i < size; i++) {
            array_set(arr, i, rand() % (250 - 100 + 1) + 100);
        }
    }
    void MinMax(Array* arr) {
        Array* vec = NULL;
        int max = array_get(arr, 0);
        
        for (int i = 0; i < array_size(arr); i++) {
            if (array_get(arr, i) > max) {
                max = array_get(arr,i);
            }
        }
        
        for (int i = 0; i < array_size(arr); i++) {
            if (array_get(arr, i) == max) {
                vec = array_create(1);
                array_set(vec, 0, i);
                break;
            }
        }
        for (int i = 0; i < array_size(arr) - 1; i++) {
            if (array_get(arr,i) == max) {
                vec = re_size(vec, i);
            }
        }
        if (array_size(vec) > 1) {
            cout << array_get(vec, 0) << " " << array_get(vec, array_size(vec) - 1)<< endl;
        }
        else {
            cout << max << endl;
        }
    }
    void Sort(Array* arr) {
        int peregon = 0;
        for (int i = 0; i < array_size(arr) - 1; i++) {
            for (int j = i + 1; j < array_size(arr); j++) {
                if (array_get(arr,j) < array_get(arr, i)) {
                    peregon = array_get(arr, i);
                    array_set(arr, i, array_get(arr, j));
                    array_set(arr, j,peregon);
                }
            }
        }
    }
    int Difference(Array* arr) {
        Sort(arr);
        int min = 1000000;
        Array* carChet = NULL;
        for (int i = 0; i < array_size(arr); i++) {
            if (array_get(arr,i) % 2 == 0) {
                carChet = array_create(1);
                array_set(carChet,0,array_get(arr,i));
                break;
            }
        }
        for (int i = 0; i < array_size(arr); i++) {
            if (array_get(arr, i) % 2 == 0) {
                carChet = re_size(carChet, array_get(arr, i));
            }
        }
        for (int i = 1; i < array_size(carChet); i++) {
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
