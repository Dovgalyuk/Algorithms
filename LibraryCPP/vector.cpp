#include "vector.h"
#include "iostream"

struct Vector
{
    size_t size;
    Data* data;
    Vector(){
        this->size = 0;
        this->data = new Data[size];
    }
    /*Vector(const Vector& prev_Vector) {
        std::cout << "copy vec";
        this->size = prev_Vector.size;
        this->data = new Data[this->size];
        for (size_t i = 0; i < this->size; i++) {
            this->data[i] = prev_Vector.data[i];
        }
    }*/
    ~Vector(){
        delete[] this->data;
    }
};

Vector* vector_create()
{
    return new Vector();
}

void vector_delete(Vector* vector)
{
    // TODO: free vector internals
    delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
    return vector->data[index];
}

void vector_set(Vector* vector, size_t index, Data value)
{
    vector->data[index] = value;
}

size_t vector_size(const Vector* vector)
{
    return vector->size;
}

void vector_resize(Vector* vector, size_t size)
{
    size_t old_size = vector->size;
    Data* new_data = new Data[size];
    if (size < old_size) {
        for (size_t i = 0; i < size; i++) {
            new_data[i] = vector->data[i];
        }
    }
    else {
        for (size_t i = 0; i < old_size; i++) {
            new_data[i] = vector->data[i];
        }
    }
    delete[] vector->data;
    vector->size = size;
    vector->data = new_data;
}
