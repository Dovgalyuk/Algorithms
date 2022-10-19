#include "vector.h"
#include <memory.h>

struct Vector
{
    Data* data;
    size_t size;
    size_t capacity;

    Vector() {
        this->size = 1; //Initial size
        this->capacity = 10;//Initial capacity
        this->data = new Data[capacity];
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
    if (size <= vector->capacity){
        vector->size = size;
    } else {
        
        size_t new_capacity = size << 1;// grow vector size * 2
        
        Data* new_data = new Data[new_capacity];
        
        memcpy(new_data,vector->data,vector_size(vector) * sizeof(Data));
        
        delete[] vector->data;
        
        vector->size = size;
        vector->capacity = new_capacity;
        vector->data = new_data;
    }  
}
