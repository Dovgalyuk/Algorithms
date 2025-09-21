#include <stdio.h>
#include <stdlib.h>
#include "array.h"

Array *array_create_and_read(FILE *input, int read_data)
{
    int n;
    printf("Attempting to read array size...\n");
    
    if (fscanf(input, "%d", &n) != 1) {
        printf("Error: Failed to read array size\n");
        return NULL;
    }
    
    if (n < 0) {
        printf("Error: Invalid array size: %d\n", n);
        return NULL;
    }
    
    printf("Array size: %d\n", n);
    
    Array *arr = array_create(n, NULL);
    if (!arr) {
        printf("Error: Failed to create array of size %d\n", n);
        return NULL;
    }
    
    if (!read_data) {
        printf("Array created\n");
        return arr;
    }
    
    printf("Reading %d elements...\n", n);
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        if (fscanf(input, "%d", &x) != 1) {
            printf("Error: Failed to read element %d\n", i);
            array_delete(arr);
            return NULL;
        }
        printf("Read element %d: %d\n", i, x);
        array_set(arr, i, x);
    }
    
    printf("Array created successfully\n");
    return arr;
}

void task1(Array *arr)
{
    if (!arr || arr->size == 0) {
        printf("Task 1 - Invalid array\n");
        return;
    }
    
    int remainder = 1;
    for (int i = 0; i < arr->size; i++) {
        remainder *= 10;
        int digit = remainder / 17;
        remainder %= 17;
        array_set(arr, i, digit);
    }
    
    printf("Task 1 - Digits of 1/17: ");
    array_print(arr);
}

void task2(Array *arr)
{
    if (!arr) {
        printf("Task 2 - Array is NULL\n");
        return;
    }
    
    if (arr->size < 5) {
        printf("Task 2 - Array too small for 5 elements (size: %d)\n", arr->size);
        printf("Array contents: ");
        array_print(arr);
        return;
    }
    
    int max_sum = 0;
    int max_start_index = 0;
    
    for (int i = 0; i <= arr->size - 5; i++) {
        int current_sum = 0;
        for (int j = 0; j < 5; j++) {
            current_sum += array_get(arr, i + j);
        }
        
        if (current_sum > max_sum) {
            max_sum = current_sum;
            max_start_index = i;
        }
    }
    
    printf("Task 2 - Max sum of 5 consecutive elements: %d\n", max_sum);
    printf("Elements: [");
    for (int i = 0; i < 5; i++) {
        printf("%d", array_get(arr, max_start_index + i));
        if (i < 4) printf(", ");
    }
    printf("]\n");
    printf("Starting index: %d\n", max_start_index);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    printf("Opening file: %s\n", argv[1]);
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        printf("Error opening file: %s\n", argv[1]);
        perror("fopen error");
        return 1;
    }
    
    Array *arr = NULL;
    
    printf("\n=== Reading array for Task 1 ===\n");
    arr = array_create_and_read(input, 0); 
    if (arr) {
        task1(arr);
        array_delete(arr);
    } else {
        printf("Failed to read array for Task 1\n");
    }
    
    printf("\n=== Reading array for Task 2 ===\n");
    arr = array_create_and_read(input, 1);
    if (arr) {
        task2(arr);
        array_delete(arr);
    } else {
        printf("Failed to read array for Task 2\n");
    }
    
    fclose(input);
    return 0;
}