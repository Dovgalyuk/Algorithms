#include "vector.h"
#include <stdexcept>

struct Vector {
    Data* elements;
    size_t size;
    size_t capacity;
};

Vector* vector_create() {
    Vector* v = new Vector;
    v->capacity = 4;
    v->size = 0;
    v->elements = new Data[v->capacity]();
    return v;
}

void vector_delete(Vector* v) {
    if (!v) return;
    delete[] v->elements;
    delete v;
}

Data vector_get(const Vector* v, size_t index) {
    if (!v || index >= v->size) throw std::runtime_error("Vector index out of bounds");
    return v->elements[index];
}

void vector_set(Vector* v, size_t index, Data value) {
    if (!v || index >= v->size) throw std::runtime_error("Vector index out of bounds");
    v->elements[index] = value;
}

size_t vector_size(const Vector* v) {
    return v ? v->size : 0;
}

void vector_resize(Vector* v, size_t new_size) {
    if (!v) return;
    if (new_size > v->capacity) {
        size_t new_capacity = v->capacity;
        while (new_capacity < new_size) new_capacity *= 2;
        Data* new_elements = new Data[new_capacity]();
        for (size_t i = 0; i < v->size; i++) new_elements[i] = v->elements[i];
        delete[] v->elements;
        v->elements = new_elements;
        v->capacity = new_capacity;
    }
    v->size = new_size;
}
