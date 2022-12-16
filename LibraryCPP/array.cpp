#include "array.h"

struct Array {
    Data* ArrayData;
    size_t ArraySize;
    Array(size_t ArraySize) {
        this->ArraySize = ArraySize;
        ArrayData = new int[this->ArraySize];
    }
    ~Array(){
        delete[] ArrayData;
    }
};

// create array
Array* array_create(size_t size) {
    return new Array(size);
}

// delete array, free memory
void array_delete(Array* arr) {
    delete arr;
}

// returns specified array element
Data array_get(const Array* arr, size_t index) {
    if (index >= array_size(arr)) {
        return 0;
    }
    else {
        return arr->ArrayData[index];
    }
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value) {
    if (array_size(arr) < index) {
        return;
    }
    else {
        arr->ArrayData[index] = value;
    }
}

// returns array size
size_t array_size(const Array* arr) {
    return arr->ArraySize;
}
