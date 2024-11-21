#include <stdlib.h>
#include "vector.h"

typedef struct Vector {
    size_t current_size;
    size_t current_capacity;
    Data* data_array;
    FFree* destruct;
    Data default_filler;
} Vector;

Vector *vector_create(FFree* destructor_func, Data initial_filler) {
    Vector* new_vector = malloc(sizeof(Vector));
    new_vector -> current_size = 0;
    new_vector -> current_capacity = 4;
    new_vector -> data_array = (Data*) malloc(sizeof(Data) * new_vector -> current_capacity);
    new_vector -> destruct = destructor_func;
    new_vector -> default_filler = initial_filler;
    return new_vector;
}

void vector_delete(Vector *vector) {
    if (vector -> destruct != NULL) {
        for (size_t i = 0; i < vector_size(vector); i++) {
            if (vector -> data_array[i] != vector -> default_filler) {
                vector -> destruct((void*) vector -> data_array[i]);
            }
        }
    }
    free(vector -> data_array);
    free(vector);
}

Data vector_get(const Vector *vector, size_t index) {
    if (index < vector_size(vector)) {
        return vector -> data_array[index];
    } else {
        return vector -> default_filler;
    }
}

void vector_set(Vector *vector, size_t index, Data value) {
    if (index < vector_size(vector)) {
        vector -> data_array[index] = value;
    } else {
        vector_resize(vector, index + 1);
        vector -> data_array[index] = value;
    }
}

size_t vector_size(const Vector *vector) {
    return vector -> current_size;
}

void vector_resize(Vector *vector, size_t new_size) {
    if (vector -> current_capacity < new_size) {
        size_t new_capacity = vector -> current_capacity;
        while (new_capacity < new_size) {
            new_capacity *= 2;
        }

        vector -> data_array = (Data*) realloc(vector -> data_array, new_capacity * sizeof(Data));
        vector -> current_capacity = new_capacity;
        for (size_t i = vector -> current_size; i < new_size; i++) {
            vector -> data_array[i] = vector -> default_filler;
        }
    }
    else if (new_size < vector -> current_size) {
        if (vector -> destruct != NULL) {
            for (size_t i = new_size; i < vector -> current_size; i++) {
                if (vector -> data_array[i] != vector -> default_filler) {
                    vector -> destruct((void*) vector -> data_array[i]);
                    vector -> data_array[i] = vector -> default_filler;
                }
            }
        }
    }
    vector -> current_size = new_size;
}
