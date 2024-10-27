#include <stdlib.h>
#include <stdio.h>
#include "array.h"

typedef struct Array 
{
    size_t size;
    Data* data;
    FFree* distruct;
} Array;

// create array
Array *array_create(size_t size, FFree f)
{
    Array* arr = malloc(sizeof(Array));
    if (arr == NULL) {
        printf("Ошибка выделения памяти для структуры");
        return NULL;
    }

    arr -> data = malloc(size * sizeof(Data));
    if (arr -> data == NULL) {
        printf("Ошибка выделения памяти для массива");
        free(arr);
        return NULL;
    }

    arr -> distruct = f;
    arr -> size = size;
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (arr == NULL) {
        printf("Ошибка удаления");
        return;
    }
    if (arr -> distruct != NULL) {
        for (size_t i = 0; i < arr->size; i++){
            void* ptr = (void*)arr->data[i];
            arr -> distruct(ptr);
        }
    }
    free(arr -> data);
    free(arr);
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (arr == NULL || index >= arr->size) {
        printf("Ошибка: массив пуст или индекс выходит за пределы");
        return 0;
    }

    return arr -> data[index];
}

// sets the specified array element to the value
int array_set(Array *arr, size_t index, Data value)
{
    if (arr == NULL || index >= arr -> size) {
        printf("Массив пуст или индекс вышел за пределы размера");
        return -1;
    }
    arr -> data[index] = value;
    return 0;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr -> size;
}
