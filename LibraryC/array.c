#include <stdlib.h>
#include "array.h"

typedef struct Array
{
    size_t size;
    Data* array;
} Array;

// create array
Array* array_create(size_t size, FFree f)
{
    if (size > 0) {
        Array* newarray = (Array*)malloc(sizeof(Array));
        newarray->size = size;
        newarray->array = (Data*)malloc(sizeof(Data) * size);
        return newarray;
    }
    else
        return malloc(sizeof(Array));
}

// delete array, free memory
void array_delete(Array* arr)
{
    free(arr);
}

// returns specified array element
Data array_get(const Array* arr, size_t index)
{
    if (index < arr->size) {
        return arr->array[index];
    }
    return (Data)0;
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value)
{
    if (index < arr->size) {
        arr->array[index] = value;
    }
    else return;
}

// returns array size
size_t array_size(const Array* arr)
{
    return arr->size;
    //return 0;
}