#include "array.h"

typedef int Data;

struct Array {
    Data* Data;
    size_t Size;
    Array(size_t size) {
        Size = size;
        Data = new int[size];
    }
    ~Array() {
        delete[] Data;
    }
};

// create array
Array* array_create(size_t size) {
    return new Array(size);
}

// delete array, free memory
void array_delete(Array* arr) {
    delete[] arr->Data;
}

// returns specified array element
Data array_get(const Array* arr, size_t index) {
    if (index >= array_size(arr)) {
        return 0;
    }
    else {
        return arr->Data[index];
    }
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value) {
    if (array_size(arr) < index) {
        return;
    }
    else {
        arr->Data[index] = value;
    }
}

// returns array size
size_t array_size(const Array* arr) {
    return arr->Size;
}
