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

    for (int i = 0; i < array_size(arr); ++i)
    {
        if (array_get(arr, i) >= a && array_get(arr, i) <= b)
        {
            int num = array_get(arr, i);
            for (int j = i + 1; j < array_size(arr); ++j) {
                array_set(arr, j-1, array_get(arr,j));
                if (j == array_size(arr) - 1)
                {
                    array_set(arr, j, num);
                }
            }
        }
    }

    for (int i = 0; i < array_size(arr); ++i) {
        if (array_get(arr, i) >= a && array_get(arr, i) <= b)
        {
            array_set(arr, i, 0);
        }
    }

    for (int i = 0; i < array_size(arr); i++) {
        std::cout << array_get(arr, i) << " ";
    }
    array_delete(arr);
}