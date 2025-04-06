#include "vector.h"
#include <stdio.h>

#define INITIAL_CAPACITY 10

struct Vector
{
    Data *data;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    Vector *vector = (Vector *)malloc(sizeof(Vector));
    if (vector == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for vector\n");
        exit(EXIT_FAILURE);
    }

    vector->data = (Data *)malloc(INITIAL_CAPACITY * sizeof(Data));
    if (vector->data == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for vector data\n");
        free(vector);
        exit(EXIT_FAILURE);
    }

    vector->size = 0;
    vector->capacity = INITIAL_CAPACITY;
    return vector;
}

void vector_delete(Vector *vector)
{
    // TODO: free vector internals
    if (vector) {
        free(vector->data);
        free(vector);
    }
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index >= vector->size) {
        fprintf(stderr, "Error: Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index >= vector->size) {
        fprintf(stderr, "Error: Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size > vector->capacity) {
        while (size > vector->capacity) {
            vector->capacity *= 2;
        }

        Data *new_data = (Data *)realloc(vector->data, vector->capacity * sizeof(Data));
        if (new_data == NULL) {
            fprintf(stderr, "Error: Failed to reallocate memory for vector\n");
            exit(EXIT_FAILURE);
        }
        vector->data = new_data;
    }

    vector->size = size;
}
