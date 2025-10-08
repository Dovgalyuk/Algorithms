#include "array.h"
using namespace std;
struct Array
{
    int n;
    Array* address;
    Data number;

};

// create array
Array *array_create(size_t n)
{
    Array* A = new Array;
    A->n = n;
    A->number = 0;
    Array* chain = A;
    for (size_t i = 0; i < n; i++){
        chain->address = new Array;
        chain = chain->address;
        chain->number = 0;
        chain->n = n;
    }
    chain->address = nullptr;

    return A;
}

// delete array, free memory
void array_delete(Array *arr)
{
    Array* chain = arr;
    while (chain!=nullptr)
    {
        Array* next = chain->address;
        delete chain;
        chain = next;
    }
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if ((arr == nullptr) || (index >= arr->n))
        return (Data)0;

    const Array* chain = arr;
    for (size_t i = 0; i < index; i++){
        if (chain == nullptr)
            return (Data)0;
        chain = chain->address;
    }
    return (chain != nullptr) ? chain->number : (Data)0;
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if ((arr == nullptr) || (index >= arr->n))
        return;
    Array* chain = arr;
    for (size_t i = 0; i < index; i++){
        if (chain == nullptr)
            return;
        chain = chain->address;
    }
}

// returns array size
size_t array_size(const Array *arr)
{
    return (arr == nullptr) ? 0 : arr->n;
}
