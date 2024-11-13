#include "vector.h"
#include <stdlib.h>
#include <string.h>

typedef struct Vector {
  Data *data;
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
  // Инициализируем все элементы NULL-ами
  for (size_t i = 0; i < INITIAL_CAPACITY; i++) {
    vector->data[i] = NULL;
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
  if (!vector || index >= vector->size)
    return NULL;
  return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value) {
  if (!vector || index >= vector->size)
    return;
  if (vector->data[index] && vector->free_func) {
    vector->free_func(vector->data[index]);
  }
  vector->data[index] = value;
}

size_t vector_size(const Vector *vector) { return vector ? vector->size : 0; }

void vector_resize(Vector *vector, size_t new_size) {
  if (new_size > vector->capacity) {
    size_t new_capacity =
        new_size > vector->capacity * 2 ? new_size : vector->capacity * 2;
    void **new_data = (void **)calloc(new_capacity, sizeof(void *));
    if (!new_data) {
      return;
    }
    for (size_t i = 0; i < vector->size; ++i) {
      new_data[i] = vector->data[i];
    }
    free(vector->data);
    vector->data = new_data;
    vector->capacity = new_capacity;
  }

  for (size_t i = vector->size; i < new_size; ++i) {
    vector->data[i] = NULL;
  }

  vector->size = new_size;
}