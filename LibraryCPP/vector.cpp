#include "vector.h"

struct Vector {
    Data *data;
    size_t size;
    size_t capacity;
};

Vector *vector_create() {
    Vector *vector = new Vector;
    vector->size = 0;
    vector->capacity = 10;
    vector->data = new Data[vector->capacity];
    return vector;
}

void vector_delete(Vector *vector) {
    if (vector != nullptr) {
        delete[] vector->data;
        delete vector; 
    }
}

Data vector_get(const Vector *vector, size_t index) {
    if (index >= vector->size) return (Data)0;
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value) {
    if (index >= vector->size) return;
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector) {
    return vector->size;
}

void vector_resize(Vector *vector, size_t size) {
    // Если новый размер равен 0, освобождаем память и обнуляем вектор
    if (size == 0) {
        delete[] vector->data;
        vector->data = nullptr;
        vector->size = 0;       
        vector->capacity = 0;  
        return;
    }

    if (size > vector->capacity) {
        size_t new_capacity = vector->capacity;

        while (new_capacity < size) {
            new_capacity = (new_capacity == 0) ? 1 : new_capacity * 2;
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
    for (size_t i = vector->size; i < size; ++i) {
        vector->data[i] = Data();
    }
}