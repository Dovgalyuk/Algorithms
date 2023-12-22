#include "vector.h"

Vector *vector_create(size_t initial_capacity) {
    Vector *vector = new Vector;
    vector->data = new std::pair<int, int>[initial_capacity]; // Change the data type
    vector->capacity = initial_capacity;
    vector->size = 0;
    return vector;
}

void vector_delete(Vector *vector) {
    delete[] vector->data;
    delete vector;
}

std::pair<int, int> vector_get(const Vector *vector, size_t index) { // Change the return type
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, std::pair<int, int> value) { // Change the data type
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector) {
    return vector->size;
}

void vector_resize(Vector *vector, size_t new_size) {
    if (new_size > vector->capacity) {
        size_t new_capacity = (vector->capacity == 0) ? 1 : vector->capacity * 2;
        while (new_size > new_capacity) {
            new_capacity *= 2;
        }

        std::pair<int, int> *new_data = new std::pair<int, int>[new_capacity]; // Change the data type
        for (size_t i = 0; i < vector->size; ++i) {
            new_data[i] = vector->data[i];
        }

        delete[] vector->data;
        vector->data = new_data;
        vector->capacity = new_capacity;
    }

    vector->size = new_size;
}