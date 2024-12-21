#include "vector.h"
#include <stdexcept>

Vector::Vector() {
    _capacity = 2;
    _size = 0;
    _vector = new Data[_capacity];
}

Vector::Vector(const Vector &a){
    _capacity = a._capacity;
    _size = a._size;

    _vector = new Data[_capacity];
    for (size_t idx = 0; idx < a._size; idx++) {
        _vector[idx] = a._vector[idx];
    }
}

Vector &Vector::operator=(const Vector &a){
    if (this != &a) {
        delete[] _vector;
        _capacity = a._capacity;
        _size = a._size;

        _vector = new Data[_capacity];
        for (size_t idx = 0; idx < a._size; ++idx) {
            _vector[idx] = a._vector[idx];
        }
    }
    return *this;
}

Vector::~Vector(){
    delete[] _vector;
    _capacity = 0;
    _size = 0;
}

size_t Vector::size() const {
    return _size;
}

size_t Vector::cap() const {
    return _capacity;
}

Data Vector::get(size_t index) const {
    if (index >= _size) throw std::out_of_range("The index is out of range");
    return _vector[index];
}

void Vector::set(size_t index, Data value) {
    if (index >= _size) throw std::out_of_range("The index is out of range");
    _vector[index] = value;
}

void Vector::resize(size_t size) {
    if (_capacity < size) {
        size_t new_capacity = size * 2;
        Data *new_vector = new Data[new_capacity];
        for (size_t idx = 0; idx < _size; idx++) {
            new_vector[idx] = _vector[idx];
        }
        delete[] _vector;
        _capacity = new_capacity;
        _vector = new_vector;
    }
    _size = size;
}

void Vector::insert(Data value) {
    resize(_size + 1);
    set(_size - 1, value);
}
