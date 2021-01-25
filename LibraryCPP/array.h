#ifndef ARRAY_H
#define ARRAY_H

// Non-resizeable array
// Stores integer values inside
typedef int Data;

typedef unsigned long long mysize_t;

struct Array;

// create array
Array *array_create(mysize_t size);

// delete array, free memory
void array_delete(Array *arr);

// returns specified array element
Data array_get(const Array *arr, mysize_t index);

// sets the specified array element to the value
void array_set(Array *arr, mysize_t index, Data value);

// returns array size
mysize_t array_size(const Array *arr);

#endif
