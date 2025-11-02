#include "vector.h"
#include <cstring>  // Для memcpy

struct Vector {
    Data* items;
    size_t size;
    size_t capacity;
};

Vector *vector_create() {
    Vector* vector = new Vector;
    vector->items = nullptr;
    vector->size = 0;
    vector->capacity = 0;
    return vector;
}

void vector_delete(Vector *vector) {
    if (vector->items) {
        delete[] vector->items;
    }
    delete vector;
}

Data vector_get(const Vector *vector, size_t index) {
    return vector->items[index];
}

void vector_set(Vector *vector, size_t index, Data value) {
    if (index >= vector->size) {
        vector_resize(vector, index + 1);
    }
    vector->items[index] = value;
}

size_t vector_size(const Vector *vector) {
    return vector->size;
}

void vector_resize(Vector *vector, size_t new_size) {
    if (new_size > vector->capacity) {
        size_t new_capacity = vector->capacity ? vector->capacity * 2 : 8;
        while (new_capacity < new_size) {
            new_capacity *= 2;
        }
        Data* new_items = new Data[new_capacity];
        if (vector->items) {
            std::memcpy(new_items, vector->items, vector->size * sizeof(Data));
            delete[] vector->items;
        }
        vector->items = new_items;
        vector->capacity = new_capacity;
    }
    vector->size = new_size;
}
