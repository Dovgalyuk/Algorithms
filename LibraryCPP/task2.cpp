#include "task2.h"

void task2(int* arr, int n, int a, int b) {
    int k = 0;

    for (int i = 0; i < n; i++) {
        if (!(arr[i] >= a && arr[i] <= b)) {
            arr[k] = arr[i];
            k++;
        }
    }

    for (int i = k; i < n; i++) {
        arr[i] = 0;
    }
}

