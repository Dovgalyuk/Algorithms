#include <iostream>
#include "array.h"

// create array
Array* array_create(size_t size)
{
    Array* arr = new Array;

    // выделяем память для массива и сохраняем указатель в объекте Array
    arr->dynamArray = new int[size];
    arr->size = size;

    return arr;
}

// delete array, free memory
void array_delete(Array* arr)
{
    delete[] arr->dynamArray;
    delete arr;
}


