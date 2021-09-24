#include "array.h"

struct Array {
    Data *data; // для хранения данных
    size_t arr_size; // для хранения размера массива
};

// create array
Array *array_create(size_t size) {
    Array *arr_ptr = new Array;
    arr_ptr->arr_size = size;
    arr_ptr->data = new Data[size];
    return arr_ptr;
}

// delete array, free memory
void array_delete(Array *arr) {
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index) {
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value) {
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr) {
    return arr->arr_size;
}
