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
        array_set(vec, 0, array_get(arr, i));
        int max = array_get(arr,0);
        for (int i = 0; i < array_size(arr); i++) {
            if (array_get(arr, i) > max) {
                max = array_get(arr,i);
            }
        }
        Array* vec = NULL;
        for (int i = 0; i < array_size(arr); i++) {
            if (array_get(arr, i) == max) {
                vec = array_create(1);
                array_set(vec, 0, i);
                break;
            }
        for (int i = 0; i < array_size(arr); i++) {
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
    void Sort() {
        int peregon = 0;
        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                if (car[j] < car[i]) {
                    peregon = car[i];
                    car[i] = car[j];
                    car[j] = peregon;
                }
            }
        }
    }
    int Difference() {
        Sort();
        int min = 1000000;
        vector<int> carChet;
        for (int i = 0; i < size; i++) {
            if (car[i] % 2 == 0) {
                carChet.push_back(car[i]);
            }
        }
        for (int i = 1; i < carChet.size(); i++) {
            if (carChet[i] - carChet[i - 1] < min && carChet[i] != carChet[i - 1]) {
                min = carChet[i] - carChet[i - 1];
            }
        }
        return min;
    }
    int main() {
        Array* arr = NULL;
        size_t size;

        cin >> size;
        arr = array_create(size);
        FillRandom(arr);
    }
