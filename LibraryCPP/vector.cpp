#include "vector.h"

struct Vector
{
    size_t size;
    size_t capacity;
    Data* data;
};

Vector *vector_create()
{
    Vector* vector = new Vector;

    vector->size = 0;
    vector->capacity = 0;
    vector->data = nullptr;

    return vector;

}

void vector_delete(Vector *vector)
{
    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size > vector->capacity) {
        size_t newCapacity = vector->capacity;


        if (newCapacity == 0) {
            newCapacity = 1;
        }

        while (newCapacity < size) {
            newCapacity *= 2;
        }

        Data* newData = new Data[newCapacity]{};

        for (size_t i = 0; i < vector->size; i++) {
            newData[i] = vector->data[i];
        }

        delete[] vector->data;

        vector->data = newData;
        vector->capacity = newCapacity;
    }

    vector->size = size;
}
