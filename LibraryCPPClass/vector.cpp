#include "vector.h"
#include <stdexcept>

Vector::Vector() : elements(nullptr), capacity_value(0), size_value(0) {
}

void Vector::copyFunc(const Vector& a) {
    elements = new Data[capacity_value];
    for (size_t i = 0; i < size_value; ++i) {
        elements[i] = a.elements[i];
    }
}

Vector::Vector(const Vector& a) : capacity_value(a.capacity_value), size_value(a.size_value) {
    copyFunc(a);
}

Vector& Vector::operator=(const Vector& a) {
    if (this != &a) {
        delete[] elements;
        capacity_value = a.capacity_value;
        size_value = a.size_value;
        copyFunc(a);
    }
    return *this;
}

Vector::~Vector() {
    delete[] elements;
}

Data Vector::get(size_t index) const {
    if (index >= size_value) {
        throw std::out_of_range("Index out of range");
    }
    return elements[index];
}

void Vector::set(size_t index, Data value) {
    if (index >= size_value) {
        throw std::out_of_range("Index out of range");
    }
    elements[index] = value;
}

size_t Vector::size() const {
    return size_value;
}

void Vector::resize(size_t size) {
    if (size > capacity_value) {
        size_t new_capacity = 1;
        if (capacity_value != 0) {
            new_capacity = capacity_value;
        }
        while (new_capacity < size) {
            new_capacity *= 2;
        }

        Data* new_data = new Data[new_capacity];
        for (size_t i = 0; i < size_value; ++i) {
            new_data[i] = elements[i];
        }
        delete[] elements;
        elements = new_data;
        capacity_value = new_capacity;
    }
    size_value = size;
}