#include "array.h"

struct Array
{
    Data* _array;
    size_t leng;

    Array(size_t arr_leng)
    {
        leng = arr_leng;
        _array = new Data[arr_leng];
    }

    ~Array()
    {
        delete[] _array;
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
    if (index < array_size(arr)) return arr->_array[index];
    else return 0;
   // return (Data)0;
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index < array_size(arr)) arr->_array[index] = value;

}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->leng;
}
