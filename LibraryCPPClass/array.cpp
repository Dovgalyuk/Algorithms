#include "array.h"

Array::Array(size_t size) : m_size(size), m_data(new Data[size])
{
}

Array::Array(const Array &a) : Array(a.m_size)
{
    std::memcpy(this->m_data,a.m_data, sizeof(Data) * a.m_size);
}

Array &Array::operator=(const Array &a)
{
    this->m_size=a.m_size;
    std::memcpy(a.m_data, this->m_data, sizeof(Data) * m_size);
    return *this;
}

Array::~Array()
{
    delete[] m_data;
}

Data Array::get(size_t index) const
{
    return *(m_data + index);
}

void Array::set(size_t index, Data value)
{
    *(m_data + index) = value;
}

size_t Array::size() const
{
    return m_size;
}
