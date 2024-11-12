#include "vector.h"
#include <cstdlib>
#include <stdexcept>



Vector *vector_create(size_t capacity)
{
    Vector *vector = new Vector;
    vector->data = nullptr; 
    vector->size = 0;                  
    vector->capacity = 0;       
    return vector;
}



void vector_delete(Vector *vector)
{
    delete[] vector->data; 
    delete vector;
}


Data vector_get(const Vector *vector, size_t index)
{
    if (index > vector->size) {
        throw std::out_of_range("Incorrect index");
    }
    return vector->data[index]; 
}


void vector_set(Vector *vector, size_t index, Data value)
{
    if (index > vector->size) {
        throw std::out_of_range("Incorrect index");
    }
    vector->data[index] = value; 
}


size_t vector_size(const Vector *vector)
{
    return vector->size;
}


void vector_resize(Vector *vector, size_t size)
{
    if (size == vector->size) {
        return;
    }

    if (size > vector->capacity) {
        size_t capacity_up = size > vector->capacity * 2 ? size : vector->capacity * 2;
        Data* data_up = new Data[capacity_up];

        for (size_t i = 0; i < vector->size; i++) {
            data_up[i] = vector->data[i];
        }

        delete[] vector->data;
        vector->data = data_up;
        vector->capacity = capacity_up;
    }

    vector->size = size;
}

