#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

typedef struct Vector {
    Data* d;
    size_t size;
    size_t copacity;
    FFree* freeFunc;
} Vector;

Vector *vector_create(FFree f)
{
    Vector* vec = (Vector*)malloc(sizeof(Vector));
    if(vec == NULL) 
        return NULL;

    vec->d = NULL;
    vec->size = 0;
    vec->copacity = 0;
    vec->freeFunc = f;

    return vec;
}

void vector_delete(Vector *vector)
{
    if(vector == NULL)
        return;

    if(vector->freeFunc != NULL) {
        for(size_t i = 0; i < vector->size; i++) {
            vector->freeFunc((void*)vector->d[i]);
        }
    }
    free(vector->d);
    free(vector);
}

Data vector_get(const Vector *vector, size_t index)
{
    if(vector == NULL || index >= vector->size || vector->d[index] == NULL)
        return (Data)0;


    return vector->d[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if(vector == NULL || index >= vector->size)
        return;

    if (vector->freeFunc != NULL && vector->d[index] != VECTOR_EMPTY ) {
        vector->freeFunc((void*)vector->d[index]);
    }
    
    vector->d[index] = value;
}

size_t vector_size(const Vector *vector)
{
    if(vector == NULL)
        return (size_t)0;

    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if(vector == NULL || vector->size == size)
        return;
    
    if(size < vector->size) {
        if(vector->freeFunc != NULL) {
            for(size_t i = size; i < vector->size; i++) {
                if(vector->d[i] != VECTOR_EMPTY) {
                    vector->freeFunc(vector->d[i]);
                    vector->d[i] = NULL;
                }
            }
        }
    }
    else if (size > vector->copacity) {
        size_t temp_copacity = (vector->copacity > 0) ? vector->copacity : (size_t)1 ;
        
        while (size > temp_copacity) {
            temp_copacity *= 2;
        } 
    
        Data *temp_arr = (Data*)realloc(vector->d, temp_copacity * sizeof(Data));
        if (temp_arr == NULL)
            return;
    
        vector->d = temp_arr;
        for (size_t i = vector->copacity; i < temp_copacity; i++) {
            vector->d[i] = VECTOR_EMPTY;
        }
        
        vector->copacity = temp_copacity;
    
    }
    vector->size = size;
}
