#include "array.h"
#include "stdlib.h"
#include <iostream>
using namespace std;

struct Array
{
    int* arr;
};

// create array
Array* array_create(size_t size)
{
    int* arr = new int[size];
    if (*arr == NULL) {
        cout << "Null pointer returned";
    }
    return new Array;
}

// delete array, free memory
void array_delete(Array* arr)
{
    delete [] arr;
}

// returns specified array element
Data array_get(const Array* arr, size_t index)
{

    return (*arr); index;
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value)
{
    (*arr); index = value;
}

// returns array size
size_t array_size(const Array* arr)
{
    return sizeof(*arr)/sizeof(arr);
}
