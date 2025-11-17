#include "vector.h"

struct Vector
{
    int* arr;
    size_t size;
    size_t capacity;
};


Vector *vector_create()
{
    Vector *vector = new Vector;
    vector->arr = nullptr;
    vector->size = 0;
    vector->capacity = 0;
    return vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->arr;
    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index >= vector->size) {
        throw std::out_of_range("Index out of range");
    }
    return vector->arr[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index >= vector->size) {
        vector_resize(vector, index + 1);
    }
    vector->arr[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size <= vector->capacity) {
        if (size > vector->size) {
            for (size_t i = vector->size; i < size; i++) {
                vector->arr[i] = 0;
            }
        }
        vector->size = size;
        return;
    }

    size_t new_capacity = vector->capacity * 2;
    if (new_capacity < size) {
        new_capacity = size;
    }

    if (new_capacity == 0) {
        new_capacity = 1;
    }

    Data* new_arr = new Data[new_capacity];
    
    for (size_t i = 0; i < vector->size; i++) {
        new_arr[i] = vector->arr[i];
    }
    
    for (size_t i = vector->size; i < size; i++) {
        new_arr[i] = 0;
    }

    delete[] vector->arr;
    vector->arr = new_arr;
    vector->size = size;
    vector->capacity = new_capacity;
}