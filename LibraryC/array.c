#include <stdlib.h>
#include "array.h"

typedef struct Array {
    size_t size;
    Data *data;
} Array;

// create array
Array *array_create(size_t size, FFree f) {
    Array *arr = (Array *)malloc(sizeof(Array));
    arr->size = size;
    arr->data = (Data *)malloc(size * sizeof(Data));  // Выделяем память под элементы
    return arr;
}

// delete array, free memory
void array_delete(Array *arr) {
}

// returns specified array element
Data array_get(const Array *arr, size_t index) {
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value) {

}

// returns array size
size_t array_size(const Array *arr) {
}