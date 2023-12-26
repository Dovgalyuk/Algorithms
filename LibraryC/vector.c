#include <stdlib.h>
#include "vector.h"

typedef struct Vector
{
} Vector;

Vector *vector_create(FFree f)
{
    return malloc(sizeof(Vector));
}

void vector_delete(Vector *vector)
{
    // TODO: free vector internals
    free(vector);
}

Data vector_get(const Vector *vector, size_t index)
{
    return (Data)0;
}

void vector_set(Vector *vector, size_t index, Data value)
{
}

size_t vector_size(const Vector *vector)
{
    return 0;
}

void vector_resize(Vector *vector, size_t size)
{
}
