#include <stdlib.h>
#include "array.h"

typedef struct Array
{
    // Data *arr;
    // size_t size;
    // FFree *f;
    void *some_variable; // need to success build finish
} Array;

// create array
Array *array_create(size_t size, FFree f)
{
    // Array *arr = (Array *)malloc(sizeof(Array));
    // arr->arr = (Data *)malloc(sizeof(Data) * size);
    // arr->f = f;
    // arr->size = size;
    // return arr;
    return NULL;
}

// delete array, free memory
void array_delete(Array *arr)
{
    //(*(arr->f))(arr->arr);
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    return NULL; // arr->arr[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    // arr->arr[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return 0; // arr->size;
}
