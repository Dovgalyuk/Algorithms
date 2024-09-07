#include "array.h"

Array::Array(size_t size) : m_size(size), m_data(new Data[size]())
{
    for(size_t i = 0; i < m_size; i++) {
        m_data[i] = 0;
    }
}

Array::Array(const Array &a) : m_size(a.m_size), m_data(new Data[a.m_size])
{
    for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = a.m_data[i];
    }
}

Array &Array::operator=(const Array &a)
{
    if (this == &a) {
        return *this;
    }

    delete[] m_data;

    m_size = a.m_size;
    m_data = new Data[m_size];

    for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = a.m_data[i];
    }

    return *this;
}

Array::~Array()
{
    delete[] m_data;
}

Data Array::get(size_t index) const
{
    if (index >= m_size) {
        throw std::out_of_range("Index out of range\n");
    }
    return m_data[index];
}

void Array::set(size_t index, Data value)
{
    if (index >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    m_data[index] = value;
}

size_t Array::size() const
{
    return m_size;
}
