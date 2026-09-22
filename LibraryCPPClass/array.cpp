#include <iostream>
#include "array.h"

Array::Array(size_t size)
{
    len = size;
    contents = new Data[size];
}

Array::Array(const Array &a)
{
    contents = new Data[a.len];
    for (int i = 0; i < a.len; i++)
        contents[i] = a.contents[i];
}

Array &Array::operator=(const Array &a)
{
    if (this != &a) {
        delete[] contents;
        contents = new Data[a.len];
        for (int i = 0; i < a.len; i++)
            contents[i] = a.contents[i];
    }
    return *this;
}

Array::~Array()
{
    delete[] contents;
}

Data Array::get(size_t index) const
{
    return contents[index];
}

void Array::set(size_t index, Data value)
{
    contents[index] = value;
}

size_t Array::size() const
{
    return len;
}


Array* array_create_and_read(FILE* input)
{
    int n;
    if(fscanf(input, "%d", &n) != 1)
        return;
    /* Create array */
    Array* arr = new Array(n);
    /* Read array data */
    for (int i = 0; i < n; ++i)
    {
        int x;
        if (fscanf(input, "%d", &x) != 1)
            return;
        arr->set(i, x);
    }
    return arr;
}