#include "vector.h"
#include <stdexcept>
struct Vector {
    Data* data;
    size_t size;
    size_t volume;
};

Vector* vector_create() {
    Vector* vector = new Vector;
    vector->size = 0;
    vector->volume = 4;
    vector->data = new Data[vector->volume];
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
    throw std::out_of_range("Index out of range");
}

void vector_set(Vector* vector, size_t index, Data value) {
    if (index >= vector->size) {
        throw std::out_of_range("Index out of range");
    }
    vector->data[index] = value;
}

size_t vector_size(const Vector* vector) {
    return vector->size;
}

void vector_resize(Vector* vector, size_t new_size) {
    if (new_size > vector->volume) {
        while (vector->volume < new_size) {
            vector->volume *= 2;
        }
        Data* new_data = new Data[vector->volume];
        for (size_t i = 0; i < vector->size; ++i) {
            new_data[i] = vector->data[i];
        }
        delete[] vector->data;
        vector->data = new_data;
    }
    vector->size = new_size;
}
