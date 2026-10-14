#include "vector.h"

struct Vector {
    int* data;
    size_t size;
    size_t capacity;
};

Vector* vector_create() {
    Vector* v = new Vector;
    v->capacity = 4;
    v->size = 0;
    v->data = new int[v->capacity];
    return v;
}

void vector_delete(Vector* v) {
    delete[] v->data;
    delete v;
}

int vector_get(const Vector* v, size_t index) {
    if (index >= v->size) 
        return 0;
    
    return v->data[index];
}

void vector_set(Vector* v, size_t index, int value) {
    if (index < v->size)
        v->data[index] = value;
}

size_t vector_size(const Vector* v) {
    return v->size;
}

void vector_resize(Vector* v, size_t new_size) 
{
    if (new_size > v->capacity) 
    {
        size_t new_cap = v->capacity * 2;
        while (new_cap < new_size) 
            new_cap *= 2;
        
        int* new_data = new int[new_cap];
        for (size_t i = 0; i < v->size; ++i)
            new_data[i] = v->data[i];
        
        delete[] v->data;
        v->data = new_data;
        v->capacity = new_cap;
    }
    v->size = new_size;
}
