#include "array.h"
#include <iostream>
#include <cstdlib>
using namespace std;

    void FillRandom(Array* arr) {
        size_t size = array_size(arr);
        cout << "Массив, заполненный случайными числами:" << endl;
        for (size_t i = 0; i < size; i++) {
            array_set(arr, i, static_cast<int>(rand() % (250 - 100 + 1) + 100));
            cout << array_get(arr, i)<<endl;
        }
    }
    void MinMax(Array* arr) {

        int max = array_get(arr, 0);
        size_t max1 = 0;
        size_t max2 = 0;

        for (size_t i = 0; i < array_size(arr); i++) {
            if (array_get(arr, i) > max) {
                max = array_get(arr, i);
                max1 = i;
            }
        }

        for (size_t i = 0; i < array_size(arr); i++) {
            if (array_get(arr, i) == max) {
                    max2 = i;
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
        carChet = array_create(1);
        for (size_t i = 0; i < array_size(arr); i++) {
            if (array_get(arr,i) % 2 == 0) {
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
    int DiffCorrect(Array* arr) {
        Sort(arr);
        int ch = 0;
        for (int i = 0; i < array_size(arr); i++) {
            if (array_get(arr, i) % 2 == 0) {
                ch++;
            }
        }
        Array* Chet = NULL;
        Chet = array_create(ch);
        for (size_t i = 0; i < array_size(Chet); i++) {
            if (array_get(arr, i) % 2 == 0) {
                array_set(Chet, i, static_cast<int>(array_get(arr, i)));
            }
        }
        int minR = 1000;
        for (size_t i = 1; i < array_size(Chet); i++) {
            if ((array_get(Chet, i) - array_get(Chet, i - 1)) < minR) {
                if (array_get(Chet, i) != array_get(Chet, i - 1)) {
                    minR = array_get(Chet, i) - array_get(Chet, i - 1);
                }
            }
        }
        if (minR != 1000) {
            return minR;
        }
        else{
             return -1;
        }
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
        cout << "Минимальная разница между скоростями автомобилей: "<<DiffCorrect(arr);
    }
