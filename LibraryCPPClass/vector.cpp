#include "vector.h"

Vector::Vector()
    : data(nullptr), length(0), capacity(0)
{
}

Vector::Vector(const Vector &a)
    : data(new Data[a.length]{}), length(a.length), capacity(a.length)
{
    for (size_t i = 0; i < length; i++) data[i] = a.data[i];
}

Vector &Vector::operator=(const Vector &a)
{
    if (this == &a) return *this;
    Data *copy = new Data[a.length]{};
    for (size_t i = 0; i < a.length; i++) copy[i] = a.data[i];
    delete[] data;
    data = copy;
    length = capacity = a.length;
    return *this;
}

Vector::~Vector()
{
    delete[] data;
}

Data Vector::get(size_t index) const
{
    return data[index];
}

void Vector::set(size_t index, Data value)
{
    data[index] = value;
}

size_t Vector::size() const
{
    return length;
}

void Vector::resize(size_t size)
{
    if (size > capacity) {
        size_t new_capacity = capacity == 0 ? 1 : capacity;
        while (new_capacity < size) new_capacity *= 2;
        Data *new_data = new Data[new_capacity]{};
        for (size_t i = 0; i < length; i++) new_data[i] = data[i];
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
    for (size_t i = length; i < size; i++) data[i] = Data();
    length = size;
}
