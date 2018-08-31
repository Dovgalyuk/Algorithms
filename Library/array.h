#ifndef ARRAY_H
#define ARRAY_H

// Non-resizeable array
// Stores integer values inside

struct Array;

// create array
Array *array_create(size_t size);

// delete array, free memory
void array_delete(Array *arr);

// returns specified array element
int array_get(Array *arr, size_t index);

// sets the specified array element to the value
void array_set(Array *arr, size_t index, int value);

// returns array size
size_t array_size(Array *arr);

#endif
