#include "vector.h"
#include <algorithm>

struct Vector
{
    size_t vecSize = 0;
    size_t vecCap = 0;
    Data* vecData = 0;
    Vector() {
        vecData = new Data[1];
        vecSize = 1;
        vecCap = 0;
    }
};

Vector* vector_create()
{
    return new Vector();
}

void vector_delete(Vector* vector)
{
    // TODO: free vector internals
    delete[] vector->vecData;
    delete[] vector;
}

Data vector_get(const Vector* vector, size_t index)
{
    return vector->vecData[index];
}

void vector_set(Vector* vector, size_t index, Data value)
{
    vector->vecData[index] = value;
}

size_t vector_size(const Vector* vector)
{
    return vector->vecSize;
}
void vector_expand(Vector* vector, size_t size) {
    if (vector->vecCap >= size) {
        return;
    }
    if (vector->vecCap == 0) {
        vector->vecCap = 1;
    }
    while (vector->vecCap < size) {
        vector->vecCap *= 2;
    }
}

void vector_copy(Vector* vector, size_t size, Data* temp) {

    for (int i = 0; i < size; i++) {
        temp[i] = vector->vecData[i];
    }
}

void vector_newData(Vector* vector, Data* temp, size_t size) {
    delete[] vector->vecData;
    vector->vecData = temp;
    vector->vecSize = size;
}

void vector_resize(Vector* vector, size_t size)
{
    if (size > vector->vecCap) {
        vector_expand(vector, size);
        Data* temp = new Data[vector->vecCap];
        vector_copy(vector, vector->vecSize, temp);
        vector_newData(vector, temp, size);
    }
    else {
        vector->vecSize = size;
    }
}
