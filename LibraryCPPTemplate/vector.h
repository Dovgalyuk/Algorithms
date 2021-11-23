#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include "exception"

class IndexOutOfBoundsException : public std::exception {
private:
    size_t _index;
public:
    explicit IndexOutOfBoundsException(size_t index) : _index(index) {}
    std::string message() {
        return "Index out of bounds";
    }
};

template <typename Data> class Vector
{
public:
// Creates vector
    Vector() //: _size(1), _internal_size(_size), _arr(new Data[_size])
    {
    _size = 1;
    _internal_size = 1;
    _arr = new Data[_size];
    }

    explicit Vector(size_t size) : _size(size), _internal_size(_size), _arr(new Data[_size])
    {
    }

// Deletes vector structure and internal data
    ~Vector()
    {
        delete[] _arr;
    }

// Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        if (index >= _size || index < 0) throw IndexOutOfBoundsException(index);
        return _arr[index];
    }

// Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if (index >= 0 && index < _size) {
            _arr[index] = value;
        } else if (index >= 0 && index < _internal_size) {
            _arr[index] = value;
            _size = index + 1;
        } else if (index >= 0 && index >= _internal_size) {
            resize(index + 1);
            _arr[index] = value;
            _size = index + 1;
        }
    }

// Retrieves current vector size
    size_t size() const
    {
        return _size;
    }

// Changes the vector size (may increase or decrease)
// Should be O(1) on average
    void resize(size_t size)
    {
        if (size > _internal_size) {
            _internal_size = size * 2;
            Data* newArr = new Data[_internal_size] { 0 };
            for (size_t i = 0; i < _size; ++i) {
                newArr[i] = _arr[i];
            }
            std::swap(_arr, newArr);
            delete[] newArr;
            _size = size;
        } else {
            _size = size;
        }
    }

private:
    Data* _arr;
    size_t _size;
    size_t _internal_size;
// private data should be here
};

#endif