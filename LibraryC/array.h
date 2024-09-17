#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <stdint.h>

// Non-resizeable array
// Stores pointer to custom user data
typedef uintptr_t Data;
// Custom function to free user pointers on delete
typedef void (FFree)(void*);

typedef struct Array Array;

#ifdef __cplusplus
extern "C" {
#endif

// create array
Array *array_create(size_t size, FFree f);

// delete array, free memory
void array_delete(Array *arr);

// returns specified array element
Data array_get(const Array *arr, size_t index);

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value);

// returns array size
size_t array_size(const Array *arr);

#ifdef __cplusplus
}
#endif

#endif
