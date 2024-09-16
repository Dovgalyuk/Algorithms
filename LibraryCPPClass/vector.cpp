#include "vector.h"

Vector::Vector(){
}

Vector::Vector(const Vector &a){
    _vector = a._vector;
}

Vector &Vector::operator=(const Vector &a){
    return *this;
}

Vector::~Vector(){
    _vector.clear();
}

Data Vector::get(size_t index) const {
    return _vector[index];
}

void Vector::set(size_t index, Data value) {
    _vector[index] = value;
}

size_t Vector::size() const {
    return _vector.size();
}

void Vector::resize(size_t size){
    _vector.resize(size);
}
