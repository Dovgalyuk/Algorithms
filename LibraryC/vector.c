#include <stdlib.h>
#include "vector.h"

// Values for returning empty vector cell
static const int empty_value = 0;

typedef struct Vector {
    Data* d;
    size_t size;
    size_t capacity;
    FFree* freeFunc;
} Vector;

Vector *vector_create(FFree f)
{
    Vector* vec = (Vector*)malloc(sizeof(Vector));
    if (vec == NULL)
        return NULL;
    
    vec->capacity = 0;
    vec->size = 0;
    vec->d = NULL;
    vec->freeFunc = f;

    return vec;
}

void vector_delete(Vector *vector)
{
    if (vector == NULL)
        return;

    if (vector->d != NULL && vector->freeFunc != NULL) {
        for (size_t i = 0; i < vector->size; i++) {
            if(vector->d[i] != NULL) {
                vector->freeFunc(vector->d[i]);
            }
        }
        free(vector->d);
    }

    free(vector);
}

Data vector_get(const Vector *vector, size_t index)
{
    if(vector == NULL || index >= vector->size)
        return (Data)0;

    if(vector->d[index] == NULL)
        return (Data)&empty_value;

    return vector->d[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (vector == NULL || index >= vector->size)
        return;

    if(vector->freeFunc != NULL && vector->d[index] != NULL) {
        if (vector->d[index] != value) {
            vector->freeFunc(vector->d[index]);
        }
    }
        
    vector->d[index] = value;
}

size_t vector_size(const Vector *vector)
{
    if(vector == NULL)
        return 0;

    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (vector == NULL)
        return;

    if (size < vector->size) {
        if (vector->freeFunc != NULL) {
            for (size_t i = size; i < vector->size; i++) {
                if(vector->d[i] != NULL) {
                    vector->freeFunc(vector->d[i]);
                }
            }
        }
    } 
    else if (size > vector->capacity) {
        size_t new_capacity = (vector->capacity == 0 ? 1 : vector->capacity);
        while (new_capacity < size) {
            new_capacity *= 2;
        }

        Data* temp = (Data*)realloc(vector->d, new_capacity * sizeof(Data));
        if(temp == NULL)
            return;

        vector->d = temp;
        for (size_t i = vector->capacity; i < new_capacity; i++) {
            vector->d[i] = NULL;
        }
        vector->capacity = new_capacity;
    }
    
    if (size > vector->size) {
        for (size_t i = vector->size; i < size; i++) {
            vector->d[i] = NULL;
        }
    }

    vector->size = size;
}

bool vector_cell_is_empty (Vector* vector, size_t index) {
    if (vector->d[index] == NULL)
        return true;
    else
        return false;
}
