#include "array.h"
#include <stdlib.h>

typedef struct Array {
  size_t size;
  Data* data; 
} Array;


// create array
Array *array_create(size_t size, FFree f) {
  Array* arr = malloc(sizeof(Array));

  if (arr == NULL) {
    return NULL;
  }
  arr->data = malloc(size * sizeof(Data));  
  if (arr->data == NULL) {
    free(arr);
    return NULL;
  }

  arr->size = size;
  return arr;
}

// delete array, free memory
void array_delete(Array *arr) {
  if (arr != NULL) {
      free(arr->data); 
      arr->data = NULL; 
      free(arr);      
  }
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value) {
  if (arr == NULL || index >= arr->size) {
    return;
  }
  arr -> data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr -> size;
}
