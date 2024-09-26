#include "array.h"

Array::Array(size_t size) : data(new Data[size]()), size_arr(size)
{
    for(size_t i = 0; i < size_arr; i+=1) {
        data[i] = 0;
    }
}

Array::Array(const Array &a) : data(new Data[a.size_arr]()), size_arr(a.size_arr)
{
    for (size_t i = 0; i < size_arr; ++i) {
        data[i] = a.data[i];
    }
}

Array &Array::operator=(const Array &a)
{
    if (this == &a) {
        return *this;
    }

    delete[] data;

    size_arr = a.size_arr;
    data = new Data[size_arr];

    for (size_t i = 0; i < size_arr; ++i) {
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
    if (index >= size_arr) {
        throw std::out_of_range("You have an error here: index out of range!\n");
    }
    return data[index];
}

void Array::set(size_t index, Data value)
{
    if (index >= size_arr) {
        throw std::out_of_range("You have an error here: index out of range!\n");
    }
    data[index] = value;
}

size_t Array::size() const
{
    return size_arr;
}
