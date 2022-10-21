#include "array.h"

struct Array
{
    Data* arr_1;
    size_t count;

    Array(size_t count)
    {
        _n = count;
        _arr = new Data[count];
    }

    ~Array()
    {
        delete[] arr_1;
    }
};

// create array
Array *array_create(size_t size)
{
    return new Array(size);
}

// delete array, free memory
void array_delete(Array *arr)
{
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (index >= array_size(arr))
        return 0;
    else
        return arr->arr_1[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index >= array_size(arr))
 	    return;
    else
        arr->arr_1[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->count;
}

int array_min(Array* arr) {
    int min = arr->arr_1[0];
    for (int i = 0; i < array_size(arr); ++i) {
        if (min > arr->arr_1[i]) {
            min = arr->arr_1[i];
        }
    }
    return min;
}

int array_max(Array* arr) {
    int max = arr->arr_1[0];
    for (int i = 0; i < array_size(arr); ++i) {
        if (max < arr->arr_1[i]) {
            max = arr->arr_1[i];
        }
    }
    return max;
}