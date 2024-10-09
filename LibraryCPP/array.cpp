#include "array.h"
#include <cstdlib>
#include <stdexcept>

using namespace std;

struct Array
{
    Array(size_t size, Data* array) {
        Array::size = size;
        Array::array = array;
    }

    size_t size;
    Data* array;
};

// create array
Array *array_create(size_t size)
{
    return new Array(size, new Data[size]);
}

// argument validation
static void argument_validation(const Array* arr, size_t index = 0)
{
    if (!arr)
        throw invalid_argument("Array pointer is null");
    if (index)
    {
        if (index >= arr->size)
            throw out_of_range("Out of range");
    }

}

// delete array, free memory
void array_delete(Array *arr)
{
    argument_validation(arr);

    delete[] arr->array;
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    argument_validation(arr, index);

    return arr->array[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    argument_validation(arr, index);

    arr->array[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    argument_validation(arr);

    return arr->size;
}
