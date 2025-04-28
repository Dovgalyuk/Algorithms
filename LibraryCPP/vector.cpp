#include "vector.h"
#include <stdexcept>
#include <algorithm>

struct Vector {
    Data* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
};

Vector* vector_create() {
    return new Vector;
}

void vector_delete(Vector* vector) {
    delete[] vector->data;
    delete vector;
}

void vector_resize(Vector* vector, size_t size) {
    if (size > vector->capacity) {
        size_t new_capacity = std::max(size, vector->capacity * 2);
        Data* new_data = new Data[new_capacity];
        for (size_t i = 0; i < vector->size; ++i)
            new_data[i] = vector->data[i];
        delete[] vector->data;
        vector->data = new_data;
        vector->capacity = new_capacity;
    }
    vector->size = size;
}

size_t vector_size(const Vector* vector) {
    return vector->size;
}

Data vector_get(const Vector* vector, size_t index) {
    if (index >= vector->size)
        throw std::out_of_range("Index out of range");
    return vector->data[index];
}

void vector_set(Vector* vector, size_t index, Data value) {
    if (index >= vector->size)
        throw std::out_of_range("Index out of range");
    vector->data[index] = value;
}