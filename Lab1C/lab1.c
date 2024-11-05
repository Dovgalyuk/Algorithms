#include <stdio.h>
#include <stdlib.h>
#include "array.h"

Array* array_create_and_read(FILE* input) {
    int n;
    fscanf_s(input, "%d", &n);
    Array* arr = array_create(n, NULL);
    for (int i = 0; i < n; ++i) {
        int x;
        fscanf_s(input, "%d", &x);
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array* arr, size_t size) {
    int min = (int)array_get(arr, 0);
    int max = (int)array_get(arr, 0);

    for (size_t i = 0; i < size; i++) {
        int value = (int)array_get(arr, i);
        if (value < min) min = value;
        if (value > max) max = value;
    }

    double threshold = (min + max) / 2;

    for (size_t i = 0; i < size; i++) {
        if ((int)array_get(arr, i) > threshold) {
            printf("%zu\n", i);
        }
    }
}

void task2(Array* arr, size_t size) {
    int* frequency = (int*)calloc(size, sizeof(int));
    if (frequency == NULL) {
        printf("Memory allocation failed for frequency array");
        return;
    }


    if (arr != NULL) {
        int most_frequent = (int)array_get(arr, 0);
        int max_count = 0;
        for (size_t i = 0; i < size; i++) {
            int current = (int)array_get(arr, i);
            if (current >= 0 && current < (int)size) {
                frequency[current]++;
                if (frequency[current] > max_count) {
                    max_count = frequency[current];
                    most_frequent = current;
                }

            }
            else {
                printf("Value is out of bounds for frequency array");
            }

        }
        printf("%d", most_frequent);
    }
    free(frequency);
}

int main()
{
    FILE* input = fopen("input.txt", "r");
    if (!input) {
        return 1;
    }
    Array* arr = array_create_and_read(input);
    size_t size = array_size(arr);
    if (arr == NULL) {
        printf("Array is NULL");
        return 1;
    }
    if (size == 0) {
        printf("Array is empty");
        return 1;
    }
    

    task1(arr, size);
    task2(arr, size);
    array_delete(arr);
    fclose(input);
    return 0;
} 
