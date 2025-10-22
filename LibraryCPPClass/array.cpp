#include "array.h"
#include <stdexcept>

Array::Array(size_t size) : size_arr(size), data_arr(new Data[size])
{
    for (size_t i = 0; i < size_arr; i++)
    {
        data_arr[i] = Data(0);
    }
}

Array::Array(const Array& other) : size_arr(other.size_arr)
{
    data_arr = new Data[size_arr];
    for (size_t i = 0; i < size_arr; i++)
    {
        data_arr[i] = other.data_arr[i];
    }
}

Array& Array::operator=(const Array& other)
{
    if (this != &other) {
        delete[] data_arr;
        size_arr = other.size_arr;
        data_arr = new Data[size_arr];

        for (size_t i = 0; i < size_arr; i++) {
            data_arr[i] = other.data_arr[i];
        }
    }
    return *this;
}

Array::~Array()
{
    delete[] data_arr;
}

Data Array::get(size_t index) const
{
    if ((index >= size_arr))
    {
        throw std::out_of_range("ERROR: index out of range");
    }
    else
    {
        return data_arr[index];
    }
}

void Array::set(size_t index, Data value)
{
    if ((index >= size_arr))
    {
        throw std::out_of_range("ERROR: index out of range");
    }
    else
    {
        data_arr[index] = value;
    }
}

size_t Array::size() const
{
    return size_arr;
}
