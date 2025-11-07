#include "vector.h"
#include <stdexcept>

struct Vector {
  Data *data;
  size_t capacity;
  size_t size;
};

Vector *vector_create() {
  Vector *vector = new Vector;
  vector->data = nullptr;
  vector->capacity = 0;
  vector->size = 0;
  return vector;
}

void vector_delete(Vector *vector) {
  if (vector->data != nullptr) {
    delete[] vector->data;
  }
  delete vector;
}

Data vector_get(const Vector *vector, size_t index) {
  if (index >= vector->size) {
    throw std::out_of_range("Index out of range");
  }
  return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value) {
  if (index >= vector->size) {
    throw std::out_of_range("Index out of range");
  }
  vector->data[index] = value;
}

size_t vector_size(const Vector *vector) { return vector->size; }

void vector_resize(Vector *vector, size_t size) {
  if (size == vector->size) {
    return;
  }

  if (size <= vector->capacity) {
    vector->size = size;
    return;
  }
  size_t new_capacity = size;
  if (size < vector->capacity * 2) {
    new_capacity = vector->capacity * 2;
  }

  Data *new_data = new Data[new_capacity];

  for (size_t i = 0; i < vector->size && i < size; i++) {
    new_data[i] = vector->data[i];
  }
  for (size_t i = vector->size; i < size; i++) {
    new_data[i] = 0;
  }

  if (vector->data != nullptr) {
    delete[] vector->data;
  }
  vector->data = new_data;
  vector->capacity = new_capacity;
  vector->size = size;
}
