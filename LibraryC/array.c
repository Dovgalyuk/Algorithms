#include "array.h"
#include <stdlib.h>

typedef struct Array {
  size_t size;
  FFree *free_fn;
  Data elements[];
} Array;

// create array
Array *array_create(size_t size, FFree f) {
  size_t total_size = sizeof(Array) + size * sizeof(Data);

  Array *arr = malloc(total_size);

  if (arr == NULL) {
    return NULL;
  }

  arr->size = size;
  arr->free_fn = f;

  for (size_t i = 0; i < size; i++) {
    arr->elements[i] = 0;
  }

  return arr;
}

// delete array, free memory
void array_delete(Array *arr) {
  if (arr == NULL) {
    return;
  }

  if (arr->free_fn != NULL) {
    for (size_t i = 0; i < arr->size; i++) {
      Data val = arr->elements[i];
      if (val != 0) {
        arr->free_fn((void *)val);
      }
    }
  }

  free(arr);
}

// returns specified array element
Data array_get(const Array *arr, size_t index) {
  if (index >= arr->size) {
    return (Data)0;
  }
  return arr->elements[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value) {
  if (index >= arr->size) {
    return;
  }

  if (arr->free_fn != NULL) {
    Data old_value = arr->elements[index];
    if (old_value != (Data)0) {
      arr->free_fn((void *)old_value);
    }
  }

  arr->elements[index] = value;
}

// returns array size
size_t array_size(const Array *arr) { return arr->size; }