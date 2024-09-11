#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <cstddef>
#include <cstdlib>

// Non-resizeable array
// Stores integer values inside
typedef int Data;
typedef unsigned int size_t;

struct Array;

// create array
Array *array_create(size_t size);

// delete array, free memory
void array_delete(Array *arr);

// returns specified array element
Data array_get(const Array *arr, size_t index);

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value);

// returns array size
size_t array_size(const Array *arr);

Array* create_random_array(Data size);

void array_erase(Array* arr, size_t index);

#endif
