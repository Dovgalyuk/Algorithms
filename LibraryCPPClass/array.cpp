#include "array.h"
#include <stdexcept>

Array::Array(size_t size)
{
    array_size = size;
    data = new Data[size];

    for (size_t i = 0; i < size; i++) {
        data[i] = 0;
    }
}

Array::Array(const Array &a)
{
    array_size = a.array_size;
    data = new Data[array_size];

    for (size_t i = 0; i < array_size; i++) {
        data[i] = a.data[i];
    }
}

Array &Array::operator=(const Array &a)
{
    if (this == &a) {
        return *this;
    }

    delete[] data;

    array_size = a.array_size;
    data = new Data[array_size];

    for (size_t i = 0; i < array_size; i++) {
        data[i] = a.data[i];
    }

    return *this;
}

Array::~Array()
{
    delete[] data;
}

Data Array::get(size_t index) const
{
    if (index >= array_size) {
        throw std::out_of_range("Index out of range");
    }

    return data[index];
}

void Array::set(size_t index, Data value)
{
    if (index >= array_size) {
        throw std::out_of_range("Index out of range");
    }

    data[index] = value;
}

Data &Array::operator[](size_t index)
{
    if (index >= array_size) {
        throw std::out_of_range("Index out of range");
    }

    return data[index];
}

size_t Array::size() const
{
    return array_size;
}