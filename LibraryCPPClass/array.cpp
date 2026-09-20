#include "array.h"

#include <algorithm>
#include <stdexcept>

Array::Array(size_t size)
    : data_(size > 0 ? new Data[size]() : nullptr), size_(size)
{
    // круглые скобки в new Data[size]() заполняют массив нулями
}

Array::Array(const Array& a)
    : data_(a.size_ > 0 ? new Data[a.size_] : nullptr), size_(a.size_)
{
    // копия владеет своей памятью, иначе память освободилась бы дважды
    std::copy(a.data_, a.data_ + a.size_, data_);
}

Array& Array::operator=(const Array& a)
{
    if (this == &a)
        return *this;

    // сначала выделяем новую память, и только потом освобождаем старую
    Data* new_data = a.size_ > 0 ? new Data[a.size_] : nullptr;
    std::copy(a.data_, a.data_ + a.size_, new_data);

    delete[] data_;
    data_ = new_data;
    size_ = a.size_;
    return *this;
}

Array::~Array()
{
    delete[] data_;
}

Data Array::get(size_t index) const
{
    if (index >= size_)
        throw std::out_of_range("Array::get: index is out of range");
    return data_[index];
}

void Array::set(size_t index, Data value)
{
    if (index >= size_)
        throw std::out_of_range("Array::set: index is out of range");
    data_[index] = value;
}

size_t Array::size() const
{
    return size_;
}