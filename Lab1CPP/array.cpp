#include "array.h"
#include <algorithm>
#include <stdexcept>

Array::Array(std::size_t size) : _size(size), _data(nullptr) {
    if (_size > 0) {
        _data = new int[_size]{};
    }
}

Array::Array(const Array& a) : _size(a._size), _data(nullptr) {
    if (_size) {
        _data = new int[_size];
        std::copy(a._data, a._data + _size, _data);
    }
}

Array& Array::operator=(const Array& a) {
    if (this == &a) return *this;
    if (a._size != _size) {
        delete[] _data;
        _size = a._size;
        _data = _size ? new int[_size] : nullptr;
    }
    if (_size) {
        std::copy(a._data, a._data + _size, _data);
    }
    return *this;
}

Array::~Array() {
    delete[] _data;
    _data = nullptr;
    _size = 0;
}

int& Array::operator[](std::size_t index) {
    if (index >= _size) throw std::out_of_range("Array index out of range");
    return _data[index];
}

const int& Array::operator[](std::size_t index) const {
    if (index >= _size) throw std::out_of_range("Array index out of range");
    return _data[index];
}

std::size_t Array::size() const {
    return _size;
}

int Array::get(std::size_t index) const {
    if (index >= _size) throw std::out_of_range("Array index out of range");
    return _data[index];
}

void Array::set(std::size_t index, int value) {
    if (index >= _size) throw std::out_of_range("Array index out of range");
    _data[index] = value;
}
