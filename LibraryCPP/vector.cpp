#include "vector.h"
#include <stdexcept>

struct Vector {
    Data *data;
    size_t size;
    size_t capacity;
};

Vector *vector_create() {
    Vector *vector = new Vector;
    vector->size = 0;
    vector->capacity = 1;
    vector->data = new Data[vector->capacity];
    return vector;
}

void vector_delete(Vector *vector) {
    delete[] vector->data;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index) {
    if (index >= vector->size) {
        throw std::out_of_range("Index is out of range");
    }
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value) {
    if (index >= vector->size) {
        vector_resize(vector, index + 1);
    }
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector) {
    return vector->size;
}

void vector_resize(Vector *vector, size_t new_size) {
    if (new_size > vector->capacity) {
        size_t new_capacity = vector->capacity;
        while (new_capacity < new_size) {
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
    vector->size = new_size;
}
