#include "array.h"

typedef struct Array {
  size_t size_struct;
  Data* data_struct;
} Array;

// create array
Array *array_create(size_t size, FFree f) {
  Array* arr = malloc(sizeof(Array));

  if (arr == NULL) {
    return NULL;
  }
  arr->data_struct = malloc(size * sizeof(Data));  
  if (arr->data_struct == NULL) {
    free(arr);
    return NULL;
  }

  arr->size_struct = size;
  return arr;
}

// delete array, free memory
void array_delete(Array *arr) {
  for (size_t i = 0; i < arr->size_struct; ++i) {
    free(arr->data_struct[i]);  
  }
  free(arr->data_struct);
  free(arr);
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    return arr->data_struct[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value) {
  if (arr == NULL || index >= arr->size_struct) {
    return;
  }
  arr->data_struct[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size_struct;
}

