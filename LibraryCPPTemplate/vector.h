#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector()
    {
        _data = nullptr;
        _size = 0;
        _capacity = 0;
    }

    // copy constructor
    Vector(const Vector &a)
    {
        _size = a._size;
        _capacity = a._capacity;
        if (_capacity > 0)
        {
            _data = new Data[_capacity];
            for (size_t i = 0; i < _size; ++i)
                _data[i] = a._data[i];
        }
        else
        {
            _data = nullptr;
        }
    }

    // assignment operator
    Vector &operator=(const Vector &a)
    {
        if (this == &a)
            return *this;

        Data* newData = nullptr;
        if (a._capacity > 0)
        {
            newData = new Data[a._capacity];
            for (size_t i = 0; i < a._size; ++i)
                newData[i] = a._data[i];
        }

        delete[] _data;

        _data = newData;
        _size = a._size;
        _capacity = a._capacity;


        return *this;
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete[] _data;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        return _data[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        _data[index] = value;
    }

    // Retrieves current vector size
    size_t size() const
    {
        return _size;
    }

    Data& operator[](size_t index)
    {
        return _data[index];
    }
    const Data& operator[](size_t index) const
    {
        return _data[index];
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t newSize)
    {
        if (newSize <= _capacity)
        {
            if (newSize > _size)
            {
                for (size_t i = _size; i < newSize; ++i)
                    _data[i] = Data();
            }
            _size = newSize;
            return;
        }

        size_t newCapacity = (_capacity == 0) ? 1 : _capacity;
        while (newCapacity < newSize)
            newCapacity *= 2;

        Data* newData = new Data[newCapacity];

        for (size_t i = 0; i < _size; ++i)
            newData[i] = _data[i];

        for (size_t i = _size; i < newSize; ++i)
            newData[i] = Data();

        delete[] _data;

        _data = newData;
        _capacity = newCapacity;
        _size = newSize;
    }

private:
    // private data should be here
    Data* _data = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;

};

#endif
