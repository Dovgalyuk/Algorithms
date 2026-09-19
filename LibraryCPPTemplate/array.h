#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

#include <cstddef>

template <typename Data> class Array
{
public:
    explicit Array(size_t size) : _size(size), _data(new Data[size])
    {
    }

    Array(const Array &a) : _size(a._size), _data(new Data[a._size])
    {
        for (size_t i = 0; i < _size; i++)
            _data[i] = a._data[i];
    }

    Array &operator=(const Array &a)
    {
        if (this != &a) {
            delete[] _data;
            _size = a._size;
            _data = new Data[_size];
            for (size_t i = 0; i < _size; i++)
                _data[i] = a._data[i];
        }
        return *this;
    }

    ~Array()
    {
        delete[] _data;
    }

    Data get(size_t index) const
    {
        return _data[index];
    }

    void set(size_t index, Data value)
    {
        _data[index] = value;
    }

    size_t size() const
    {
        return _size;
    }

private:
    size_t _size;
    Data *_data;
};

#endif