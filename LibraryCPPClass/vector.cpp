#include "vector.h"

Vector::Vector() : data(nullptr), sz(0), capacity(0)
{
}

Vector::Vector(const Vector &a) : data(nullptr), sz(a.sz), capacity(a.capacity)
{
    if (capacity > 0) {
        data = new Data[capacity];
        for (size_t i = 0; i < sz; ++i)
            data[i] = a.data[i];
    }
}

Vector &Vector::operator=(const Vector &a)
{
    if (this != &a) {
        Data* new_data = (a.capacity > 0) ? new Data[a.capacity] : nullptr;
        for (size_t i = 0; i < a.sz; ++i) new_data[i] = a.data[i];
        delete[] data;
        data = new_data;
        sz = a.sz;
        capacity = a.capacity;
    }
    return *this;
}

Vector::~Vector()
{
    delete[] data;
}

Data Vector::get(size_t index) const
{
    if (index >= sz)
        throw std::out_of_range("Vector::get: index out of range");
    return data[index];
}

void Vector::set(size_t index, Data value)
{
    if (index >= sz)
        throw std::out_of_range("Vector::set: index out of range");
    data[index] = value;
}

size_t Vector::size() const
{
    return sz;
}

void Vector::resize(size_t new_size)
{
    if (new_size > capacity) {
        size_t new_cap = (capacity > 0) ? capacity : 1;
        while (new_cap < new_size) {
            new_cap *= 2;
        }

        Data* new_data = new Data[new_cap];
        for (size_t i = 0; i < sz; ++i) {
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
        capacity = new_cap;
    }
    sz = new_size;
}
