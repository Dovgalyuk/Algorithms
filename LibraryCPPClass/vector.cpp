#include "vector.h"

Vector::Vector() : _data(nullptr), _capacity(0), _size(0) {}

Vector::Vector(const Vector& a) : _data(nullptr), _capacity(0), _size(0)
{
    if (a._capacity > 0) {
        copy_from(a._data, a._capacity, a._size);
    }
}

Vector& Vector::operator=(const Vector& a)
{
    if (this != &a)
    {
        delete[] _data;
        _data = nullptr;
        _capacity = 0;
        _size = 0;
        if (a._capacity > 0) {
            copy_from(a._data, a._capacity, a._size);
        }
    }

    return *this;
}

Vector::~Vector()
{
    delete[] _data;
}

Data Vector::get(size_t index) const
{
    return index < _size ? _data[index] : Data();
}

void Vector::set(size_t index, Data value)
{
    if (index < _size)
    {
        _data[index] = value;
    }
}

size_t Vector::size() const
{
    return _size;
}

void Vector::resize(size_t size)
{
    if (size > _capacity)
    {
        size_t new_capacity = _capacity == 0 ? 1 : _capacity;
        while (new_capacity < size)
        {
            new_capacity *= 2;
        }

        Data* new_data = new Data[new_capacity];
        for (size_t i = 0; i < _size; i++)
        {
            new_data[i] = _data[i];
        }

        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }

    if (size > _size)
    {
        for (size_t i = _size; i < size; ++i)
        {
            _data[i] = Data();
        }
    }

    _size = size;
}

void Vector::copy_from(const Data* data, size_t capacity, size_t size)
{
    _data = new Data[capacity];
    _capacity = capacity;
    _size = size;
    for (size_t i = 0; i < size; i++)
    {
        _data[i] = data[i];
    }
}
