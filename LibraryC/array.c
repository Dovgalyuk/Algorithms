#include <stdlib.h>
#include "array.h"

typedef struct Array
{
} Array;

// create array
Array *array_create(size_t size, FFree f)
{
    return malloc(sizeof(Array));
}

// delete array, free memory
void array_delete(Array *arr)
{
    free(arr);
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    return (Data)0;
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
}

// returns array size
size_t array_size(const Array *arr)
{
    return 0;
}
