#include "vector.h"
#include <cstdlib>

struct Vector {
    Data *data;
    size_t capacity;
    size_t size;
};

Vector *vector_create() {
    Vector *v = new Vector;
    v->capacity = 4;
    v->size = 0;
    v->data = new Data[v->capacity];
    return v;
}

void vector_delete(Vector *vector) {
    if (vector) {
        delete[] vector->data;
        delete vector;
    }
}

Data vector_get(const Vector *vector, size_t index) {
    if (index < vector->size) {
        return vector->data[index];
    }
    return (Data)0;
}

void vector_set(Vector *vector, size_t index, Data value) {
    if (index < vector->size) {
        vector->data[index] = value;
    }
}

size_t vector_size(const Vector *vector) {
    return vector->size;
}

void vector_resize(Vector *vector, size_t size) {
    if (size > vector->capacity) {
        size_t new_capacity = vector->capacity * 2;
        //if (new_capacity == 0) new_capacity = 1;
        while (new_capacity < size) {
            new_capacity *= 2;
        }
        Data *new_data = new Data[new_capacity];
        for (size_t i = 0; i < vector->size; ++i) {
            new_data[i] = vector->data[i];
        }
        delete[] vector->data;
        vector->data = new_data;
        vector->capacity = new_capacity;
    }
    vector->size = size;
}