#include "array.h"
using namespace std;
struct Array
{
    size_t n;
    int* arr;

};

// create array
Array* array_create(size_t n)
{
    Array* A = new Array;
    A->n = n;
    A->arr = new int[n];
    return A;
}

// delete array, free memory
void array_delete(Array* arr)
{
    delete[] arr->arr;
    delete arr;
}

// returns specified array element
Data array_get(const Array* arr, size_t index)
{
    return arr->arr[index];
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value)
{
    arr->arr[index] = value;
}

// returns array size
size_t array_size(const Array* arr)
{
    return arr->n;
}
