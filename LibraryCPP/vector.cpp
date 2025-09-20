/*#include "vector.h"

struct Vector
{
};

Vector *vector_create()
{
    return new Vector;
}

void vector_delete(Vector *vector)
{
    // TODO: free vector internals
    delete vector; 
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
*/


#include "vector.h"

#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif

struct Vector
{
};

Vector* vector_create()
{
    return new Vector;
}

void vector_delete(Vector* vector)
{
    // TODO: free vector internals
    delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
    UNUSED(vector);
    UNUSED(index);
    return (Data)0;
}

void vector_set(Vector* vector, size_t index, Data value)
{
    UNUSED(vector);
    UNUSED(index);
    UNUSED(value);
}

size_t vector_size(const Vector* vector)
{
    UNUSED(vector);
    return 0;
}

void vector_resize(Vector* vector, size_t size)
{
    UNUSED(vector);
    UNUSED(size);
}