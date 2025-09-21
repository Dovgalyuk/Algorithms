#include <stdio.h>
#include <stdlib.h>
#include "array.h"

Array *array_create_and_read(FILE *input, int read_data)
{
    int n;
    
    if (fscanf(input, "%d", &n) != 1) {
        return NULL;
    }
    
    if (n < 0) {
        return NULL;
    }
    
    Array *arr = array_create(n, NULL);
    if (!arr) {
        return NULL;
    }
    
    if (!read_data) {
        return arr;
    }
    
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        if (fscanf(input, "%d", &x) != 1) {
            array_delete(arr);
            return NULL;
        }
        array_set(arr, i, x);
    }
    
    return arr;
}

void task1(Array *arr)
{
    if (!arr || arr->size == 0) {
        return;
    }
    
    int remainder = 1;
    for (int i = 0; i < arr->size; i++) {
        remainder *= 10;
        int digit = remainder / 17;
        remainder %= 17;
        array_set(arr, i, digit);
    }
    
    array_print(arr);
}

void task2(Array *arr)
{
    if (!arr) {
        return;
    }
    
    if (arr->size < 5) {
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
    
    for (int i = 0; i < 5; i++) {
        printf("%d", array_get(arr, max_start_index + i));
        if(i<4){
            printf(" ");
        }
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        return 1;
    }
    
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        perror("fopen error");
        return 1;
    }
    
    Array *arr = NULL;
    
    arr = array_create_and_read(input, 0); 
    if (arr) {
        task1(arr);
        array_delete(arr);
    }
    
    arr = array_create_and_read(input, 1);
    if (arr) {
        task2(arr);
        array_delete(arr);
    }
    
    fclose(input);
    return 0;
}