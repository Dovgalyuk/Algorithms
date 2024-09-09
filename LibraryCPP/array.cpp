#include "array.h"

struct Array {
    size_t size;
    Data *arr;
};

// create array
Array *array_create(size_t size) {
    Array *newArray = new Array;
    newArray->size = size;
    newArray->arr = (Data*) new Data[size];
    return newArray;
}

// delete array, free memory
void array_delete(Array *arr) {
    delete[] arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index) {
    return (Data) arr->arr[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value){
    arr->arr[index] = value;
}

// returns array size
size_t array_size(const Array *arr){
    return arr->size;
}
