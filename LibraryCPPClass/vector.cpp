#include "vector.h"

#include <algorithm>
#include <stdexcept>

Vector::Vector()
    : data_(nullptr), size_(0), capacity_(0)
{
}

Vector::Vector(const Vector &a)
    : data_(a.size_ > 0 ? new Data[a.size_] : nullptr), size_(a.size_), capacity_(a.size_)
{
    std::copy(a.data_, a.data_ + a.size_, data_);
}

Vector &Vector::operator=(const Vector &a)
{
    if (this == &a)
        return *this;

    // сначала выделяем новую память, и только потом освобождаем старую
    Data* new_data = a.size_ > 0 ? new Data[a.size_] : nullptr;
    std::copy(a.data_, a.data_ + a.size_, new_data);
    
    delete[] data_;
    data_ = new_data;
    size_ = a.size_;
    capacity_ = a.size_;
    return *this;
}

Vector::~Vector()
{
    delete[] data_;
}

Data Vector::get(size_t index) const
{
    if (index >= size_)
        throw std::out_of_range("Vector::get: index is out of range");
    return data_[index];
}

void Vector::set(size_t index, Data value)
{
    if (index >= size_)
        throw std::out_of_range("Vector::set: index is out of range");
    data_[index] = value;
}

size_t Vector::size() const
{
    return size_;
}

void Vector::resize(size_t size)
{
    if (size > capacity_)
    {
        // Память увеличиваем минимум в два раза. Поэтому копирование
        // происходит редко, и resize в среднем работает за O(1).
        const size_t new_capacity = std::max(size, capacity_ * 2);
        Data* new_data = new Data[new_capacity];
        std::copy(data_, data_ + size_, new_data);

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    // новые элементы заполняем нулями
    if (size > size_)
        std::fill(data_ + size_, data_ + size, Data());

    size_ = size;
}
