#include "array.h"
#include "task2.h"

void task2(Array* arr, int a, int b)
{
    int k = 0;

    for (size_t i = 0; i < array_size(arr); i++) {
        int value = array_get(arr, i);
        if (!(value >= a && value <= b)) {
            array_set(arr, k, value);
            k++;
        }
    }

    for (size_t i = k; i < array_size(arr); i++) {
        array_set(arr, i, 0);
    }
}



