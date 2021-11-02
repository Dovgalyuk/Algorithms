#include "arrayC.h"

typedef struct ArrayC
{
    int x;
} ArrayC;

// create array
ArrayC *array_create(size_t size, FFree f)
{
    return malloc(sizeof(ArrayC));
}

// delete array, free memory
void array_delete(ArrayC *arr)
{
    free(arr);
}

// returns specified array element
Data array_get(const ArrayC *arr, size_t index)
{
    return (Data)0;
}

// sets the specified array element to the value
void array_set(ArrayC *arr, size_t index, Data value)
{
}

// returns array size
size_t array_size(const ArrayC *arr)
{
    return 0;
}
