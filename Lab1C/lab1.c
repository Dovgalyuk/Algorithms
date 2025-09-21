#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

void fill_with_1_over_17_digits(Array* arr) {
    size_t size = array_size(arr);
    if (size == 0) return;
    
    int remainder = 1;
    for (size_t i = 0; i < size; i++) {
        remainder *= 10;
        int digit = remainder / 17;
        remainder = remainder % 17;
        array_set(arr, i, (Data)digit);
    }
}

void find_max_sum_of_five(Array* arr) {
    size_t size = array_size(arr);
    if (size < 5) {
        printf("Array size is less than 5\n");
        return;
    }
    
    long long max_sum = 0;
    size_t max_start_index = 0;
    
    for (size_t i = 0; i < 5; i++) {
        max_sum += (long long)array_get(arr, i);
    }
    
    long long current_sum = max_sum;
    
    for (size_t i = 5; i < size; i++) {
        current_sum = current_sum - (long long)array_get(arr, i - 5) + (long long)array_get(arr, i);
        if (current_sum > max_sum) {
            max_sum = current_sum;
            max_start_index = i - 4;
        }
    }
    
    for (size_t i = max_start_index; i < max_start_index + 5; i++) {
        printf("%d", (int)array_get(arr, i));
        if (i < max_start_index + 4) {
            printf(" ");
        }
    }
    printf("\n");
}

int read_int_from_file(FILE* file) {
    int value;
    fscanf(file, "%d", &value);
    return value;
}

void read_array_from_file(Array* arr, FILE* file) {
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; i++) {
        int value;
        fscanf(file, "%d", &value);
        array_set(arr, i, (Data)value);
    }
}

void print_array(Array* arr) {
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; i++) {
        printf("%d", (int)array_get(arr, i));
        if (i < size - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", argv[1]);
        return 1;
    }

    int size1 = read_int_from_file(file);
    Array* arr1 = array_create(size1, NULL);
    
    fill_with_1_over_17_digits(arr1);
    print_array(arr1);
    
    array_delete(arr1);
    
    int size2 = read_int_from_file(file);
    Array* arr2 = array_create(size2, NULL);
    
    read_array_from_file(arr2, file);
    find_max_sum_of_five(arr2);
    
    array_delete(arr2);
    fclose(file);
    
    return 0;
}
