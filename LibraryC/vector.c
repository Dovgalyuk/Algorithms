#include "vector.h"
#include <stdlib.h>
#include <string.h>

typedef struct Vector {
  Data *data;
  size_t size;
  size_t capacity;
  FFree free_func;
} Vector;

Vector *vector_create(FFree f) {
  Vector *vector = malloc(sizeof(Vector));
  if (!vector)
    return NULL;
  vector->data = NULL;
  vector->size = 0;
  vector->capacity = 0;
  vector->free_func = f;
  return vector;
}

void vector_delete(Vector *vector) {
  if (vector->free_func) {
    for (size_t i = 0; i < vector->size; ++i) {
      vector->free_func(vector->data[i]);
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
  vector->data[index] = value;
}

size_t vector_size(const Vector *vector) { return vector->size; }

void vector_resize(Vector *vector, size_t size) {
  if (size > vector->capacity) {
    vector->capacity = size * 2;
    Data *new_data = realloc(vector->data, vector->capacity * sizeof(Data));
    if (!new_data) {
      // Обработка ошибки выделения памяти
      return;
    }
    vector->data = new_data;
  }
  vector->size = size;
}
