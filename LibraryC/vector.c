#include <stdlib.h>
#include "vector.h"

typedef struct Vector {
    Data d; // заглушка
} Vector;

Vector* vector_create(FFree f)
{
    (void)f;
    return malloc(sizeof(Vector));
}

void vector_delete(Vector* vector)
{
    (void)vector;
    free(vector);
}

Data vector_get(const Vector* vector, size_t index)
{
    (void)vector;
    (void)index;
    return 0;
}

void vector_set(Vector* vector, size_t index, Data value)
{
    (void)vector;
    (void)index;
    (void)value;
}

size_t vector_size(const Vector* vector)
{
    (void)vector;
    return 0;
}

void vector_resize(Vector* vector, size_t size)
{
    (void)vector;
    (void)size;
}
