#include <iostream>
#include "array.h"

Array::Array(size_t size) : _size(size), _array(new Data[size]()) {
    for(size_t i = 0; i < _size; i++) {
        _array[i] = 0;
    }
}

Array::Array(const Array &a) : _size(a._size), _array(new Data[a._size]){
    for (size_t i = 0; i < _size; i++) {
        _array[i] = a._array[i];
    }
}

Array &Array::operator=(const Array &a) {
    if (this == &a) return *this;
    delete[] _array;

    _size = a._size;
    _array = new Data[_size];

    for (size_t i = 0; i < _size; ++i) {
        _array[i] = a._array[i];
    }

    return *this;
}

Array::~Array() {
    delete[] _array;
}

Data Array::get(size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Index out of range\n");
    }
    return _array[index];
}

void Array::set(size_t index, Data value) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range\n");
    }
    _array[index] = value;
}

size_t Array::size() const {
    return _size;
}
