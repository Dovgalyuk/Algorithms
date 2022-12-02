#include "vector.h"

struct Vector
{
    Data* data;
    size_t size;
    size_t capacity;

    Vector() {
        this->size = 0;
        this->capacity = 5;
        this->data = new Data[capacity];
    }

    ~Vector() {
        delete[] data;
    }
};

Vector *vector_create()
{
    return new Vector;
}

void vector_delete(Vector *vector)
{
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    size_t size = vector_size(vector);
    if (index<size) {
        return vector->data[index];
    } 
    else {
        throw "You entered wrong index!";
    }
}

void vector_set(Vector *vector, size_t index, Data value)
{
    size_t size = vector_size(vector);
    if (index < size) {
        vector->data[index] = value;
    } 
    else {
        throw "You entered wrong index! Use function «vector_resize» to change vector size.";
    }
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (vector->capacity>size)
    {
        vector->size = size;
    }
    else {
        size_t temp_capacity = vector->capacity * 2;
        Data* temp_data = new Data[temp_capacity];

        for (int i = 0; i < vector->size; i++)
        {
            temp_data[i] = vector->data[i];
        }

        delete[] vector->data;

        vector->capacity = temp_capacity;
        vector->size = size;
        vector->data = temp_data;
    }
    
}
