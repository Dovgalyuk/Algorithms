#include <iostream>
#include <climits>
#include <ctime>
#include "array.h"

int main() {
    srand(time(0));
    int a = 0, b = 0, n;
    std::cin >> n >> a >> b;
    Array *arr = array_create(n);
    for (int i = 0; i < array_size(arr); i++) {
        /*int k;
        std::cin >> k;
        array_set(arr, i, k);*/
        array_set(arr, i, rand() % 500 - 100);
    }


    for (int i = 0; i < array_size(arr) - 1; ++i) {

        if (array_get(arr, i) >= a && array_get(arr, i) <= b){

            int firstNonZero = i + 1;
            for (int j = firstNonZero; j < array_size(arr); ++j) {
                if (array_get(arr, j) != (array_get(arr, i) >= a && array_get(arr, i) <= b)) {
                    firstNonZero = j;
                    break;
                }
            }
            int num = array_get(arr, firstNonZero);
            int num2 = array_get(arr, i);
            array_set(arr, i, num);
            array_set(arr, firstNonZero, num2);
        }
    }

    for (int i = 0; i < array_size(arr); i++) {
        if (array_get(arr, i) >= a && array_get(arr, i) <= b) {
            array_set(arr, i, 0);
        }
    }

    for (int i = 0; i < array_size(arr); i++) {
        std::cout << array_get(arr, i) << " ";
    }
    array_delete(arr);
}