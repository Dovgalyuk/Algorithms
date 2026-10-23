#include "array.h"
#include <stdexcept>
#include <utility>

Array::Array(size_t size) : data(new Data[size]), array_size(size)
{
    for (size_t i = 0; i < array_size; ++i)
        data[i] = Data(0);
}

Array::Array(const Array &a) : data(new Data[a.array_size]), array_size(a.array_size)
{
    copyForm(a);
}

Array &Array::operator=(const Array &a)
{
    if (this == &a)
        return *this;

    Array temp(a);
    std::swap(data, temp.data);
    std::swap(array_size, temp.array_size);

    return *this;
}

Array::~Array()
{
    delete[] data;
}

Data Array::get(size_t index) const
{
    if (index >= array_size)
        throw std::out_of_range("Array::get: index out of range");
    return data[index];
}

void Array::set(size_t index, Data value)
{
    if (index >= array_size)
        throw std::out_of_range("Array::set: index out of range");
    data[index] = value;
}

size_t Array::size() const
{
    return array_size;
}

void Array::copyForm(const Array& a)
{
    for (size_t i = 0; i < array_size; ++i)
        data[i] = a.data[i];
}
