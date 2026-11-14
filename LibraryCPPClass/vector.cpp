#include "vector.h"
#include <stdexcept>

Vector::Vector()
{
    data = nullptr;
    length = 0;
    capacity = 0;
}

Vector::Vector(const Vector& a)
{
    length = a.length;
    capacity = a.capacity;

    if (capacity > 0)
    {
        data = new Data[capacity];

        for (size_t i = 0; i < length; i++)
        {
            data[i] = a.data[i];
        }
    }
    else
    {
        data = nullptr;
    }
}

Vector& Vector::operator=(const Vector& a)
{
    if (this == &a)
    {
        return *this;
    }

    Data* new_data = nullptr;

    if (a.capacity > 0)
    {
        new_data = new Data[a.capacity];

        for (size_t i = 0; i < a.length; i++)
        {
            new_data[i] = a.data[i];
        }
    }

    delete[] data;

    data = new_data;
    length = a.length;
    capacity = a.capacity;

    return *this;
}

Vector::~Vector()
{
    delete[] data;
}

Data Vector::get(size_t index) const
{
    if (index >= length)
    {
        throw std::out_of_range("Vector index out of range");
    }

    return data[index];
}

void Vector::set(size_t index, Data value)
{
    if (index >= length)
    {
        throw std::out_of_range("Vector index out of range");
    }

    data[index] = value;
}

size_t Vector::size() const
{
    return length;
}

void Vector::resize(size_t size)
{
    if (size > capacity)
    {
        size_t new_capacity = (capacity == 0) ? 1 : capacity;

        while (new_capacity < size)
        {
            new_capacity *= 2;
        }

        Data* new_data = new Data[new_capacity];

        for (size_t i = 0; i < length; i++)
        {
            new_data[i] = data[i];
        }

        delete[] data;

        data = new_data;
        capacity = new_capacity;
    }

    length = size;
}
