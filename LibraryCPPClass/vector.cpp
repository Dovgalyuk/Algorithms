#include "vector.h"
#include <stdexcept>

Vector::Vector() = default;

Vector::Vector(const Vector &a)
{
    if (&a == this || !a.m_data)
    {
        return;
    }
    this->m_data = new Data[a.m_capacity];
    this->m_capacity = a.m_capacity;
    this->m_size = a.m_size;
    for (size_t i = 0; i < a.m_capacity; i++)
    {
        this->m_data[i] = a.m_data[i];
    }
}

Vector &Vector::operator=(const Vector &a)
{
    if (&a == this)
    {
        return *this;
    }
    if (this->m_data)
    {
        delete[] m_data;
    }
    this->m_data = new Data[a.m_capacity];
    this->m_capacity = a.m_capacity;
    this->m_size = a.m_size;
    for (size_t i = 0; i < a.m_capacity; i++)
    {
        this->m_data[i] = a.m_data[i];
    }

    return *this;
}

Vector::~Vector()
{
    delete[] m_data;
}


Data Vector::get(size_t index) const
{
    if (index > m_size)
    {
        throw std::out_of_range("Incorrect index");
    }
    return m_data[index];
}

void Vector::set(size_t index, Data value)
{
    if (index > m_size)
    {
        throw std::out_of_range("Incorrect index");
    }

    m_data[index] = value;
}

size_t Vector::size() const
{
    return m_size;
}

void Vector::resize(size_t size)
{
    if (size == m_size)
    {
        return;
    }

    if (size > m_capacity)
    {
        size_t newCapacity = size * 2;
        auto newData = new Data[newCapacity];
        for (size_t i = 0; i < m_size; i++)
        {
            newData[i] = m_data[i];
        }
        if (m_data)
        {
            delete[] m_data;
        }
        m_capacity = newCapacity;
        m_data = newData;
    }
    m_size = size;
}