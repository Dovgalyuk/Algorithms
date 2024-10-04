#include <iostream>
#include "lab1.h"

Array* array_create_and_read(FILE *input)
{
    int n; 
    if (fscanf(input, "%d", &n) != 1){
        return nullptr;
        }
    /* Create array */
    Array *arr = array_create(n);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        if (fscanf(input, "%d", &x) != 1) {
            array_delete(arr);
            return nullptr;
        }
        array_set(arr, i, x);
    }
    return arr;
}
// Task 1: Найти сумму элементов массива, кратных a или b. a и b ввести с клавиатуры. 
int task1(Array *arr, FILE *input)
{
    int a,b;
    if (fscanf(input,"%d %d", &a,&b) != 2){
        return 0;
    }
    int sum = 0;
    for (size_t i = 0; i < array_size(arr); i++){
        int value = array_get(arr,i);
        if (value % a == 0 || value % b == 0){
            sum += value;
        }
    }
    return sum;
}
// Task 2: В массиве найти элементы, которые не делятся ни на какой другой элемент массива. 
Array* task2(Array *arr, size_t &result_size)
{
    size_t count = 0;

    for (size_t i = 0; i < array_size(arr); i++){
        int current = array_get(arr, i);
        size_t j = 0;
        for (; j < array_size(arr); j++){
            if (i != j && current % array_get(arr, j) == 0){
                break;
            }
        }
        if (j == array_size(arr)){
            count++;
        }
    }

    Array* result = array_create(count);
    result_size = count;
    size_t index = 0;

    for (size_t i = 0; i < array_size(arr); i++){
        int current = array_get(arr, i);
        size_t j = 0;
        for (; j < array_size(arr); j++){
            if (i != j && current % array_get(arr, j) == 0){
                break;
            }
        }
        if (j == array_size(arr)){
            array_set(result, index++, current);
        }
    }

    return result;
}

