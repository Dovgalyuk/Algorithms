#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

typedef struct {
    int* data;
    size_t size;
} Array;

Array* array_create(size_t size);
void array_destroy(Array* arr);
int array_get(Array* arr, size_t index);
void array_set(Array* arr, size_t index, int value);
size_t array_size(Array* arr);

#endif