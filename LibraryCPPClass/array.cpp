#include <iostream>
#include "array.h"

Array::Array(size_t size) {
    _size = size;
    _array = (Data*) new Data[size];
}

Array::~Array() {
    delete[] _array;
}

Array::Array(const Array &a){
    _size = a._size;
    for (size_t i = 0; i < _size; i++) {
        set(i, a._array[i]);
    }
}

Array &Array::operator=(const Array &a)
{
    return *this;
}

Data Array::get(size_t index) const {
    return (Data) _array[index];
}

Data *Array::getAddress(size_t index) const {
    return (Data*) &_array[index];
}

void Array::set(size_t index, Data value) {
    _array[index] = value;
}

size_t Array::size() const {
    return _size;
}
