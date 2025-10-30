#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "array.h"

Array* array_create_and_read(FILE* input)
{
    int n;
    fscanf(input, "%d", &n);
    Array* arr = array_create(n, NULL);
    for (int i = 0; i < n; ++i)
    {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array* arr)
{
    if (arr == NULL || arr->size == 0) {
        printf("Task 1: Array is empty\n");
        return;
    }

    int min = array_get(arr, 0);
    int max = array_get(arr, 0);

    for (int i = 1; i < arr->size; i++) {
        int current = array_get(arr, i);
        if (current < min) min = current;
        if (current > max) max = current;
    }

    double average = (min + max) / 2.0;
    int count = 0;

    printf("=== Task 1 ===\n");
    printf("Array: ");
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", array_get(arr, i));
    }
    printf("\n");
    printf("Min: %d, Max: %d, Average: %.1f\n", min, max, average);
    printf("Indices of elements less than average: ");

    for (int i = 0; i < arr->size; i++) {
        if (array_get(arr, i) < average) {
            printf("%d ", i);
            count++;
        }
    }
    printf("\nTotal count: %d\n\n", count);
}

void task2(Array* arr)
{
    if (arr == NULL || arr->size == 0) {
        printf("Task 2: Array is empty\n");
        return;
    }

    printf("=== Task 2 ===\n");
    printf("Array: ");
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", array_get(arr, i));
    }
    printf("\n");
    printf("Elements that appear exactly twice: ");

    int found = 0;

    for (int i = 0; i < arr->size; i++) {
        int count = 0;
        int already_counted = 0;

        for (int k = 0; k < i; k++) {
            if (array_get(arr, k) == array_get(arr, i)) {
                already_counted = 1;
                break;
            }
        }

        if (!already_counted) {
            for (int j = 0; j < arr->size; j++) {
                if (array_get(arr, i) == array_get(arr, j)) {
                    count++;
                }
            }

            if (count == 2) {
                printf("%d ", array_get(arr, i));
                found = 1;
            }
        }
    }

    if (!found) {
        printf("None");
    }
    printf("\n\n");
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    Array* arr = NULL;
    FILE* input = fopen(argv[1], "r");
    if (!input) {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }

    printf("=== Array Processing Program ===\n\n");

    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    fclose(input);
    return 0;
}