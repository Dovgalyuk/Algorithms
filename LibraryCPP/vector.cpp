#include "vector.h"

struct Vector {
    size_t size;
    size_t capacity;
    Data* data;
};

Vector *vector_create() {
    Vector *v = new Vector();
    v->size = 0;
    v->capacity = 0;
    v->data = nullptr;
    return v;
}

void vector_delete(Vector *vector) {
    if (vector) {
        delete[] vector->data;
        delete vector;
    }
}

Data vector_get(const Vector *vector, size_t index) {
    if (vector && index < vector->size) return vector->data[index];
    return (Data)0;
}

void vector_set(Vector *vector, size_t index, Data value) {
    if (vector && index < vector->size) vector->data[index] = value;
}

size_t vector_size(const Vector *vector) {
    return vector ? vector->size : 0;
}

void vector_resize(Vector *vector, size_t size) {
    if (!vector) return;
    if (size > vector->capacity) {
        size_t new_cap = (vector->capacity == 0) ? 4 : vector->capacity * 2;
        while (new_cap < size) new_cap *= 2;
        Data* new_data = new Data[new_cap];
        for (size_t i = 0; i < vector->size; ++i) new_data[i] = vector->data[i];
        delete[] vector->data;
        vector->data = new_data;
        vector->capacity = new_cap;
    }
    for (size_t i = vector->size; i < size; ++i) vector->data[i] = 0;
    vector->size = size;
}