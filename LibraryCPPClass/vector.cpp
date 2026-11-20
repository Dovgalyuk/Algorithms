#include "vector.h"
#include <algorithm>

Vector::Vector() = default;

Vector::Vector(const Vector &a)
{
    *this = a;
}

Vector &Vector::operator=(const Vector &a)
{
    if (this != &a) {
        resize(a.size());
        for (size_t i = 0; i < length; ++i)
            data[i] = a.data[i];
    }
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
        size_t newCapacity = std::max(size, capacity * 2);
        Data *next = new Data[newCapacity];
        for (size_t i = 0; i < length; ++i)
            next[i] = data[i];
        delete[] data;
        data = next;
        capacity = newCapacity;
    }
    for (size_t i = length; i < size; ++i)
        data[i] = 0;
    length = size;
}
