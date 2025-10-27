#ifndef ARRAY_H
#define ARRAY_H

typedef int Data;

int* array_create(int size);

void array_delete(int* arr);

Data array_get(const int* arr, int index);

void array_set(int* arr, int index, int value);

int array_size(const int* arr, int size);

#endif
