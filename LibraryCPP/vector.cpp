#include "vector.h"
#include <iostream>

struct Vector {
    Data* data;
    size_t size;
    size_t capacity;
};

Vector* vector_create() {
    Vector* vector = new Vector;
    vector->size = 0;
    vector->capacity = 2;
    vector->data = new Data[vector->capacity];
    return vector;
}

void vector_delete(Vector* vector) {
    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector* vector, size_t index) {
    return vector->data[index];
}

void vector_set(Vector* vector, size_t index, Data value) {
    if (index >= vector->capacity) {
        vector_resize(vector, index + 1);
    }
    vector->data[index] = value;
    if (index >= vector->size) {
        vector->size = index + 1;
    }
}

size_t vector_size(const Vector* vector) {
    return vector->size;
}

void vector_resize(Vector* vector, size_t size) {
    if (size > vector->capacity) {
        vector->capacity = size * 2;
        Data* new_data = new Data[vector->capacity];
        for (size_t i = 0; i < vector->size; ++i) {
            new_data[i] = vector->data[i];
        }
        delete[] vector->data;
        vector->data = new_data;
    }
}

void vector_pop(Vector* vector) {
    if (vector->size > 0) {
        vector->size--;
    }
}
