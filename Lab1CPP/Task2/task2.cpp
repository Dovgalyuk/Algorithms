#include "array.h"
#include "task2.h"

size_t task2(Array *arr) {
    size_t count = array_size(arr);

    if (count < 5) {
        return 0;
    }

    size_t begin = 0, start = 0, end = 5;
    double maxsumm = 0;

    for (size_t i = 0; i < 5; i++) {
        maxsumm += array_get(arr, i);
    }

    double summ = maxsumm;

    while (end < count) {
        summ = summ - array_get(arr, start) + array_get(arr, end);
        if (summ > maxsumm) {
            maxsumm = summ;
            begin = start + 1;
        }
        start++;
        end++;
    }

    return begin;
}