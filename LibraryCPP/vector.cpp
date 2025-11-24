#include "vector.h"
#include <cstdlib>
#include <stdexcept>
#include <algorithm> 

struct Vector {
    Data* data;
    size_t sz;
    size_t cap;
};

Vector* vector_create() {
    Vector* v = new Vector;
    v->data = nullptr;
    v->sz = 0;
    v->cap = 0;
    return v;
}

void vector_delete(Vector* v) {
    if (!v) return;
    delete[] v->data;
    delete v;
}

Data vector_get(const Vector* v, size_t index) {
    if (!v || index >= v->sz) throw std::out_of_range("vector_get out of range");
    return v->data[index];
}

void vector_set(Vector* v, size_t index, Data value) {
    if (!v || index >= v->sz) throw std::out_of_range("vector_set out of range");
    v->data[index] = value;
}

size_t vector_size(const Vector* v) {
    if (!v) return 0;
    return v->sz;
}

void vector_resize(Vector* v, size_t new_size) {
    if (!v) throw std::runtime_error("vector_resize: null vector");

    if (new_size > v->cap) {
        size_t newcap = v->cap ? v->cap * 2 : 4;
        while (newcap < new_size) newcap *= 2;

        Data* newdata = new Data[newcap];
        for (size_t i = 0; i < v->sz; i++) {
            newdata[i] = v->data[i];  
        }

        delete[] v->data; 
        v->data = newdata;
        v->cap = newcap;
    }

    v->sz = new_size;
}
