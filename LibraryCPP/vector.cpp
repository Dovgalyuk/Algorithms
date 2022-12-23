#include "vector.h"

struct Vector
{
    Data* data;
    size_t size;
    size_t capacity;

    Vector() {
        this->size = 0;
        this->capacity = 10;
        this->data = new Data[capacity]{ NULL };
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
    // TODO: free vector internals
    
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    size_t size = vector_size(vector);
    
    if (index < size) {
        return vector->data[index];
    }

    else return false;
}

void vector_set(Vector *vector, size_t index, Data value)
{
    size_t size = vector_size(vector);
    if (index < size) {
        vector->data[index] = value;
    }
  
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (vector->capacity > size) vector->size = size;
    else {
        size_t new_capacity = size * 2;
        Data* new_data = new Data[new_capacity]{NULL};

        //Из сторого вектора записываем занчени в новый
        for (int i = 0; i < vector->size; i++) new_data[i] = vector->data[i]; 

        delete[] vector->data;

        vector->capacity = new_capacity;
        vector->size = size;
        vector->data = new_data;
    }

}
