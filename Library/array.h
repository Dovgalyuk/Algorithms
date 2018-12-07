#include <stdlib.h>
#include <iostream>
using namespace std;

#ifndef ARRAY_H
#define ARRAY_H

//define size mas
#define ArrSize 3000

struct Array;

// create array
Array* array_create(size_t size);

// delete array, free memory
void array_delete(Array *arr);

// returns array size
size_t array_size(Array *arr);

//set array size
void set_array_size(Array *arr, int size);

//get pointer
int* get_pointer(Array *arr, int index);
#endif
