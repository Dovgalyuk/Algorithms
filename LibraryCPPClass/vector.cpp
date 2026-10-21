#include "vector.h"
#include <utility>

Vector::Vector() : data(nullptr), sz(0), capacity(0)
{
}

Data* Vector::copy_data(const Vector& a)
{
    if (a.capacity == 0)
        return nullptr;
    Data* new_data = new Data[a.capacity];
    for (size_t i = 0; i < a.sz; ++i)
        new_data[i] = a.data[i];
    return new_data;
}

Vector::Vector(const Vector &a) : data(copy_data(a)), sz(a.sz), capacity(a.capacity)
{
}

Vector &Vector::operator=(const Vector &a)
{
    if (this != &a) {
        Data* new_data = copy_data(a);
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
