#include "vector.h"

struct Vector {
    Data* data;
    size_t capacity;
    size_t size;
};

Vector* vector_create() {
    Vector* vector = new Vector;
    vector->size = 0;
    vector->capacity = 4;
    vector->data = new Data[vector->capacity];
    return vector;
}

void vector_delete(Vector* vector) {
    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector* vector, size_t index) {
    if (index < vector->size) {
        return vector->data[index];
    }
    else {
        return -1;
    }
}

void vector_set(Vector* vector, size_t index, Data value) {
    if (index < vector->size) {
        vector->data[index] = value;
    }
}

size_t vector_size(const Vector* vector) {
    return vector->size;
}

void vector_resize(Vector* vector, size_t new_size) {
    if (new_size > vector->capacity) {
        while (vector->capacity < new_size) {
            vector->capacity *= 2;
        }
        Data* new_data = new Data[vector->capacity];
        for (size_t i = 0; i < vector->size; ++i) {
            new_data[i] = vector->data[i];
        }
        delete[] vector->data;
        vector->data = new_data;
    }
    vector->size = new_size;
}
