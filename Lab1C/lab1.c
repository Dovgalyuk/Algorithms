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

void task1(Array *arr) {
    if (!arr) return;

    int maxElement = array_get(arr, 0);
    int firstMaxElement = 0;
    int lastMaxElement = 0;

    for (int i = 0; i < array_size(arr); i++) {
        if (array_get(arr, i) > maxElement) {
            maxElement = array_get(arr, i);
            firstMaxElement = i;
            lastMaxElement = i;
        } else if (array_get(arr, i) == maxElement) {
            lastMaxElement = i;
        }
    }

    printf("%d %d", firstMaxElement, lastMaxElement);
}


void task2(Array *arr) {
    if (!arr) return;
    int maxSum = 0;
    for (int i = 0; (array_size(arr) >= 5) && (i <= array_size(arr) - 5); i++) {
        int sum = array_get(arr, i) + array_get(arr, i + 1) + array_get(arr, i + 2) +
                     array_get(arr, i + 3) + array_get(arr, i + 4);
        if (sum > maxSum) {
            maxSum = sum;
        }
    }

    printf("%d", maxSum);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    Array *arr = NULL;
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        return 1;
    }

    arr = array_create_and_read(input);
    if (arr) {
        task1(arr);
        array_delete(arr);
    } else {
        fclose(input);
        return 1;
    }

    arr = array_create_and_read(input);
    if (arr) {
        task2(arr);
        array_delete(arr);
    } else {
        fclose(input);
        return 1;
    }

    fclose(input);
    return 0;
}
