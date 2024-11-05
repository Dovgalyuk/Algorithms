#include <stdio.h>
#include <stdlib.h>

#include "array.h"

Array *array_create_and_read(FILE *input) {
    int n;

    fscanf(input, "%d", &n);

    /* Create array */
    Array *arr = array_create(n, NULL);

    /* Read array data */
    for (int i = 0; i < n; ++i) {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr, size_t size) {
    if (!arr) return;

    int maxElement = array_get(arr, 0);
    int firstMaxElement = 0;
    int lastMaxElement = 0;


    for (int i = 0; i < (int)size; i++) {
        if ((int)array_get(arr, i) > maxElement) {
            maxElement = (int)array_get(arr, i);
            firstMaxElement = i;
            lastMaxElement = i;
        } else if ((int)array_get(arr, i) == maxElement) {
            lastMaxElement = i;
        }
    }

    printf("%d %d", firstMaxElement, lastMaxElement);
}


void task2(Array *arr, size_t size) {
    if (!arr) return;
    int maxSum = 0;
    for (size_t i = 0; (size >= 5) && (i <= size - 5); i++) {
        int sum = (int)(array_get(arr, i) + array_get(arr, i + 1) + array_get(arr, i + 2) +
                     array_get(arr, i + 3) + array_get(arr, i + 4));
        if (sum > maxSum) {
            maxSum = sum;
        }
    }

    printf("%d", maxSum);
}

int main() {
    FILE *input = fopen("input.txt", "r");
    if (!input) {
        return 1;
    }

    Array *arr = array_create_and_read(input);
    size_t size = array_size(arr);
    task1(arr, size);
    task2(arr, size);

    array_delete(arr);

    fclose(input);
    return 0;
}
