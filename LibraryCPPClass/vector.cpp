#include "vector.h"

Vector::Vector()
{
    data_array = nullptr;
    current_size = 0;
    capacity = 0;
}

Vector::Vector(const Vector &a)
{
    current_size = a.current_size;
    capacity = a.capacity;
    if (capacity > 0)
    {
        data_array = new Data[capacity];
        for (size_t i = 0; i < current_size; ++i)
        {
            data_array[i] = a.data_array[i];
        }
    }
    else
    {
        data_array = nullptr;
    }
}

Vector &Vector::operator=(const Vector &a)
{
    if (this != &a)
    {
        Vector copy(a);

        Data *temp_data = data_array;
        data_array = copy.data_array;
        copy.data_array = temp_data;

        size_t temp_size = current_size;
        current_size = copy.current_size;
        copy.current_size = temp_size;

        size_t temp_cap = capacity;
        capacity = copy.capacity;
        copy.capacity = temp_cap;
    }
    return *this;
}

Vector::~Vector()
{
    delete[] data_array;
}

Data Vector::get(size_t index) const
{
    return data_array[index];
}

void Vector::set(size_t index, Data value)
{
    if (index < current_size)
    {
        data_array[index] = value;
    }
}

size_t Vector::size() const
{
    return current_size;
}

void Vector::resize(size_t size)
{
    if (size <= capacity)
    {
        for (size_t i = current_size; i < size; ++i)
        {
            data_array[i] = Data();
        }
        current_size = size;
        return;
    }

    size_t new_capacity = (capacity == 0) ? size : capacity * 2;
    if (new_capacity < size)
    {
        new_capacity = size;
    }

    Data *new_data = new Data[new_capacity];
    for (size_t i = 0; i < current_size; ++i)
    {
        new_data[i] = data_array[i];
    }
    for (size_t i = current_size; i < size; ++i)
    {
        new_data[i] = Data();
    }

    delete[] data_array;
    data_array = new_data;
    capacity = new_capacity;
    current_size = size;
}
