#include "vector.h"

struct Vector {
    Data* data;
    size_t size;
    size_t capacity;
};

static void ensure_capacity(Vector* v, size_t need) {
    if (need <= v->capacity)
        return;

    size_t newcap = (v->capacity == 0 ? 1 : v->capacity);
    while (newcap < need)
        newcap *= 2;

    Data* nd = new Data[newcap];
    const size_t to_copy = (v->size < newcap) ? v->size : newcap;

    for (size_t i = 0; i < to_copy; ++i)
        nd[i] = v->data[i];
    for (size_t i = to_copy; i < newcap; ++i)
        nd[i] = 0;

    delete[] v->data;
    v->data = nd;
    v->capacity = newcap;
}

Vector* vector_create() {
    Vector* v = new Vector;
    v->data = nullptr;
    v->size = 0;
    v->capacity = 0;
    return v;
}

void vector_delete(Vector* v) {
    delete[] v->data;
    delete v;
}

Data vector_get(const Vector* v, size_t index) {
    return v->data[index];
}

void vector_set(Vector* v, size_t index, Data value) {
    v->data[index] = value;
}

size_t vector_size(const Vector* v) {
    return v->size;
}

void vector_resize(Vector* v, size_t new_size) {
    if (new_size > v->capacity)
        ensure_capacity(v, new_size);

    if (new_size > v->size)
        for (size_t i = v->size; i < new_size; ++i)
            v->data[i] = 0;

    v->size = new_size;
}