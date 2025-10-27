#include "array.h"
#include "task2.h"

void task2(int* arr, int n, int a, int b)
{
    int k = 0;

    for (int i = 0; i < array_size(arr, n); i++) {
        int value = array_get(arr, i);
        if (!(value >= a && value <= b)) {
            array_set(arr, k, value);
            k++;
        }
    }

    for (int i = k; i < array_size(arr, n); i++) {
        array_set(arr, i, 0);
    }
}


