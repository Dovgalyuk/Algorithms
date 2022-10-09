#include "vector.h"

struct Vector
{
    Data* data;
    size_t size;

    Vector() {
        this->size = 1; //Initial size
        this->data = new Data[size];
    }

    ~Vector() {
        delete[] data;
    }
};

Vector *vector_create()
{
    return new Vector();
}

void vector_delete(Vector *vector)
{
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    size_t size = vector_size(vector);
    if (index < size)
        return vector->data[index];
    else 
        return Data();
}

void vector_set(Vector *vector, size_t index, Data value)
{
    size_t size = vector_size(vector);
    if (index < size) 
        vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    size_t cur_size = vector_size(vector);

    if (cur_size == size) return;
    
    size_t count = cur_size > size ? size : cur_size;
    Data* new_data = new Data[size];

    for (int i = 0; i < count; i++) {
        new_data[i] = vector_get(vector, i);
    }

    delete[] vector->data;
    
    vector->size = size;
    vector->data = new_data;
}
