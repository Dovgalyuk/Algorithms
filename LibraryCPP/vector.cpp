#include "vector.h"
#include <algorithm>

Vector* vector_create() {
    Vector* vector = new Vector;
    vector->size = 0;
    vector->capacity = 8;
    vector->data = new Data[vector->capacity];
    return vector;
}

void vector_delete(Vector* vector) {
    if (vector != nullptr) {
        delete[] vector->data;
        delete vector;
    }
}

Data vector_get(const Vector* vector, size_t index) {
    if (index >= vector->size) {
        throw std::out_of_range("Index out of range");
    }
    return vector->data[index];
}

void vector_set(Vector* vector, size_t index, const Data& value) {
    vector_resize(vector, index + 1);
    vector->data[index] = value;
}

size_t vector_size(const Vector* vector) {
    return vector->size;
}

void vector_resize(Vector* vector, size_t size) {
    if (size > vector->capacity) {
        size_t new_capacity = std::max(vector->capacity * 2, size);
        Data* new_data = new Data[new_capacity];

        std::copy(vector->data, vector->data + vector->size, new_data);
        delete[] vector->data;

        vector->data = new_data;
        vector->capacity = new_capacity;
    }
    vector->size = size;
}
