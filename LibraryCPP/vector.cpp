#include "vector.h"

struct Vector
{
    size_t size;
    Data* data;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->data = nullptr;
    vector->size = 0;
    return vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->data;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    return (index >= vector_size(vector))? -1 : vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (vector->size == index)
        vector_resize(vector, (index + 1) );

    if (index < vector_size(vector)) {
        vector->data[index] = value;
    }
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (vector->size >= size) {
        vector->size = size;
    }
    else {
        Data* temp = new Data[size];
        for (size_t i = 0; i < vector->size; i++) {
            temp[i] = vector->data[i];
        }
        delete[] vector->data;
        vector->data = temp;
        vector->size = size;
    }
}
