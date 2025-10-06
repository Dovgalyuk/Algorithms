#include <stdio.h>
#include "array.h"

Array *array_create_and_read(FILE *input)
{
    int n;
    fscanf(input, "%d", &n);
    /* Create array */
    Array *arr = array_create(n, NULL);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr)
{
    if (!arr) return;
    
    size_t size = array_size(arr);
    size_t max_odd_length = 0;
    size_t current_odd_length = 0;
    
    for (size_t i = 0; i < size; i++) {
        Data value = array_get(arr, i);
        
        // Check if number is odd
        if (value % 2 == 1) {
            current_odd_length++;
        } else {
            // End of odd sequence, update max if needed
            if (current_odd_length > max_odd_length) {
                max_odd_length = current_odd_length;
            }
            current_odd_length = 0;
        }
    }
    
    // Check last sequence
    if (current_odd_length > max_odd_length) {
        max_odd_length = current_odd_length;
    }
    
    printf("Maximum length of consecutive odd numbers: %zu\n", max_odd_length);
}

void task2(Array *arr)
{
    if (!arr) return;
    
    size_t size = array_size(arr);
    if (size == 0) return;
    
    // For this example, let's shift left by 2 positions
    int shift_steps = 2;
    char direction = 'L'; // L for left, R for right
    
    printf("Original array: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", (int)array_get(arr, i));
    }
    printf("\n");
    
    // Create temporary array to store shifted values
    Data *temp = malloc(size * sizeof(Data));
    if (!temp) return;
    
    // Initialize with zeros
    for (size_t i = 0; i < size; i++) {
        temp[i] = 0;
    }
    
    if (direction == 'L') {
        // Shift left
        for (size_t i = 0; i < size; i++) {
            if (i + shift_steps < size) {
                temp[i] = array_get(arr, i + shift_steps);
            }
        }
    } else {
        // Shift right
        for (size_t i = 0; i < size; i++) {
            if (i >= shift_steps) {
                temp[i] = array_get(arr, i - shift_steps);
            }
        }
    }
    
    // Copy back to original array
    for (size_t i = 0; i < size; i++) {
        array_set(arr, i, temp[i]);
    }
    
    free(temp);
    
    printf("Array after shifting %s by %d positions: ", 
           (direction == 'L') ? "left" : "right", shift_steps);
    for (size_t i = 0; i < size; i++) {
        printf("%d ", (int)array_get(arr, i));
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    Array *arr = NULL;
    FILE *input = fopen(argv[1], "r");
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    fclose(input);
}
