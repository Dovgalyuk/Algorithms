#include <stdio.h>
#include <stdlib.h>
#include "array.h"

Array *array_create(int size, int *initial_data)
{
    Array *arr = (Array *)malloc(sizeof(Array));
    if (!arr) return NULL;
    
    arr->size = size;
    arr->data = (int *)malloc(size * sizeof(int));
    if (!arr->data) {
        free(arr);
        return NULL;
    }
    
    if (initial_data) {
        for (int i = 0; i < size; i++) {
            arr->data[i] = initial_data[i];
        }
    }
    
    return arr;
}

void array_delete(Array *arr)
{
    if (arr) {
        free(arr->data);
        free(arr);
    }
}

void array_set(Array *arr, int index, int value)
{
    if (arr && index >= 0 && index < arr->size) {
        arr->data[index] = value;
    }
}

int array_get(Array *arr, int index)
{
    if (arr && index >= 0 && index < arr->size) {
        return arr->data[index];
    }
    return 0;
}

void array_print(Array *arr)
{
    if (!arr) {
        printf("NULL array\n");
        return;
    }

    for (int i = 0; i < arr->size; i++) {
        printf("%d", array_get(arr, i));
        if (i < arr->size - 1) {
            printf(" ");
        }
    }
    printf("\n");
}