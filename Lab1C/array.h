#ifndef ARRAY_H
#define ARRAY_H

typedef struct Array {
    int size;
    int *data;
} Array;

Array *array_create(int size, int *initial_data);
void array_delete(Array *arr);
void array_set(Array *arr, int index, int value);
int array_get(Array *arr, int index);
void array_print(Array *arr);

#endif