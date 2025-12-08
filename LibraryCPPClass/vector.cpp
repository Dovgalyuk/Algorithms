#include "vector.h"

Vector::Vector() : _size(0), _capacity(0), _data(nullptr) {}

Vector::Vector(const Vector &a) : _size(0), _capacity(0), _data(nullptr)
{
    *this = a;
}

Vector &Vector::operator=(const Vector &a)
{
    if (this != &a)
    {
        delete[] _data;

        _size = a._size;
        _capacity = a._capacity;
        if(_capacity > 0)
        {
            _data = new Data[_capacity];
            std::copy(a._data, a._data + _size, _data);
        }
        else
        {
            _data = nullptr;
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
    if (index >= _size)
    {
        throw std::runtime_error("Out of Range!");
    }
    return _data[index];
}

void Vector::set(size_t index, Data value)
{
    if (index >= _size)
    {
        throw std::runtime_error("Out of Range!");
    }
    _data[index] = value;
}

size_t Vector::size() const
{
    return _size;
}

void Vector::resize(size_t size)
{
    if(size == _size)
    {
        return;
    }

    if (size > _capacity)
    {
        size_t new_capacity = std::max(size, _capacity*2);
        if (new_capacity == 0) new_capacity = 1;

        Data* new_data = new Data[new_capacity];

        if (_data != nullptr && _size > 0)
        {
            std::copy(_data, _data + _size, new_data);
        }
            
            
        for (size_t i = _size; i < size; ++i)
        {
            new_data[i] = Data();
        }

        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }
    else if (size > _size)
    {
        for (size_t i = _size; i < size; ++i)
        {
            _data[i] = Data();
        }
    }

    _size = size;
}
