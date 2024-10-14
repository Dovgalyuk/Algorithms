#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

// Non-resizeable array
// Stores integer values inside
typedef int Data;

struct Array;

// create array
Array* array_create(size_t size);

// returns array size
size_t array_size(const Array* arr);

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value);

// returns specified array element
Data array_get(const Array* arr, size_t index);

// delete array, free memory
void array_delete(Array* arr);

#endif