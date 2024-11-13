#include "vector.h"
#include <stdlib.h>
#include <string.h>

typedef struct Vector {
  Data *data;
  Data fill;
  size_t size;
  size_t capacity;
  FFree *free_func;
} Vector;

#define INITIAL_CAPACITY 4

Vector *vector_create(FFree *f) {
  Vector *vector = malloc(sizeof(Vector));
  if (!vector)
    return NULL;
  vector->data = malloc(INITIAL_CAPACITY * sizeof(Data));
  if (!vector->data) {
    free(vector);
    return NULL;
  }
  vector->size = 0;
  vector->capacity = INITIAL_CAPACITY;
  vector->free_func = f;
  return vector;
}

void vector_delete(Vector *vector) {
  if (!vector)
    return;
  if (vector->free_func) {
    for (size_t i = 0; i < vector->size; ++i) {
      if (vector->data[i]) {
        vector->free_func(vector->data[i]);
      }
    }
  }
  free(vector->data);
  free(vector);
}

Data vector_get(const Vector *vector, size_t index) {
  if (index >= vector->size)
    return NULL;
  return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value) {
  if (index >= vector->size)
    return;
  if (vector->data[index] && vector->free_func) {
    vector->free_func(vector->data[index]);
  }
  vector->data[index] = value;
}

size_t vector_size(const Vector *vector) { return vector->size; }

void vector_resize(Vector *vector, size_t new_size) {
  if (vector->capacity < new_size) {
    size_t new_capacity = vector->capacity;
    while (new_capacity < new_size)
      new_capacity *= 2;

    vector->data = (Data *)realloc(vector->data, new_capacity * sizeof(Data));
    vector->capacity = new_capacity;
    for (size_t i = vector->size; i < new_size; i++)
      vector->data[i] = vector->fill;

  } else if (new_size < vector->size) {
    if (vector->free_func != NULL) {
      for (size_t i = new_size; i < vector->size; i++) {
        if (vector->data[i] != vector->fill) {
          vector->free_func((void *)vector->data[i]);
          vector->data[i] = vector->fill;
        }
      }
    }
  }
  vector->size = new_size;
}
