#include "array.h"

#include <string.h>

Array::Array(size_t size) : m_size(size), m_array((m_size) ? new Data[m_size] : nullptr) {}

Array::Array(const Array &a) : Array(a.m_size)
{
    memcpy(m_array, a.m_array, m_size * sizeof(Data));
}

Array &Array::operator=(const Array a)
{
    delete[] m_array;
    m_array = a.m_array;
    m_size = a.m_size;
    return *this;
}

Array::~Array()
{
    delete[] m_array;
}

Data Array::get(size_t index) const
{
    return m_array[index];
}

void Array::set(size_t index, Data value)
{
    m_array[index] = value;
}

size_t Array::size() const
{
    return m_size;
}
