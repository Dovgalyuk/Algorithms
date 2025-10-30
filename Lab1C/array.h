#ifndef ARRAY_H
#define ARRAY_H

typedef struct Array {
    int* data;
    int size;
} Array;

Array* array_create(int size, int* data);
void array_set(Array* arr, int index, int value);
int array_get(Array* arr, int index);
void array_delete(Array* arr);

#endif