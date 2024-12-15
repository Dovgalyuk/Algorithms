#include "vector.h"
#include <stdlib.h>
#include <string.h>

struct Vector {
    Data* data;
    size_t size;
    size_t capacity;
    FFree free_func;
};

Vector* vector_create(FFree f) {
    Vector* vector = malloc(sizeof(Vector));
    if (!vector) return NULL;
    vector->size = 0;
    vector->capacity = 4;
    vector->data = malloc(vector->capacity * sizeof(Data));
    if (!vector->data) {
        free(vector);
        return NULL;
    }
    for (size_t i = 0; i < vector->capacity; ++i) {
        vector->data[i] = NULL;
    }
    vector->free_func = f;
    return vector;
}

void vector_delete(Vector* vector) {
    if (vector) {
        if (vector->free_func) {
            for (size_t i = 0; i < vector->size; ++i) {
                if (vector->data[i]) {
                    vector->free_func(vector->data[i]);
                }
            }
        }
        free(vector->data);
        free(vector);
    }
}

Data vector_get(const Vector* vector, size_t index) {
    if (index < vector->size) {
       return vector->data[index];
    }
    else {
       return NULL;
    }
    
}

void vector_set(Vector* vector, size_t index, Data value) {
    if (index >= vector->capacity) {
        vector_resize(vector, index + 1);
    }
    if (index >= vector->size) {
        vector->size = index + 1;
    }
    if (vector->data[index] && vector->free_func) {
        vector->free_func(vector->data[index]);
    }
    vector->data[index] = value;
}

size_t vector_size(const Vector* vector) {
    return vector->size;
}

void vector_resize(Vector* vector, size_t new_size) {
    if (new_size > vector->capacity) {
        while (vector->capacity < new_size) {
            vector->capacity *= 2;
        }
        Data* new_data = malloc(vector->capacity * sizeof(Data));
        if (new_data == NULL) {
            return;
        }
        memcpy(new_data, vector->data, vector->size * sizeof(Data));
        for (size_t i = vector->size; i < vector->capacity; ++i) {
            new_data[i] = NULL;
        }
        free(vector->data);
        vector->data = new_data;
    }
    for (size_t i = vector->size; i < new_size; ++i) {
        vector->data[i] = NULL;
    }
    vector->size = new_size;
}