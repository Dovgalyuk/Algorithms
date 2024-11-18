#include "vector.h"
#include <stdexcept>

Vector::Vector() = default;

Vector::Vector(const Vector &a)
{
    if (&a == this || !a.m_dataAllocStart)
    {
        return;
    }
    this->m_dataAllocStart = new Data[a.m_capacity];
    this->m_dataStart=this->m_dataAllocStart;
    this->m_capacity = a.m_capacity;
    this->m_size = a.m_size;
    for (size_t i = 0; i < a.m_capacity; i++)
    {
        this->m_dataStart[i] = a.m_dataStart[i];
    }
}

Vector &Vector::operator=(const Vector &a)
{
    if (&a == this)
    {
        return *this;
    }
    if (this->m_dataAllocStart)
    {
        delete[] m_dataAllocStart;
    }
    this->m_dataAllocStart = new Data[a.m_capacity];
    this->m_dataStart = m_dataAllocStart;
    this->m_capacity = a.m_capacity;
    this->m_size = a.m_size;
    for (size_t i = 0; i < a.m_capacity; i++)
    {
        this->m_dataStart[i] = a.m_dataStart[i];
    }

    return *this;
}

Vector::~Vector()
{
    delete[] m_dataAllocStart;
}

void Vector::erase_first()
{
    if (m_size == 0)
    {
        throw std::out_of_range("Trying to delete out of range");
    }
    m_dataStart++;//двигаем указатель, сделано чтобы сохранить сложность О(1). 
    //Данные удалятся при следующем resize или в деструкторе
    m_size--;
    m_capacity--;
}

Data Vector::get(size_t index) const
{
    if (index > m_size || index < 0)
    {
        throw std::out_of_range("Incorrect index");
    }
    return m_dataStart[index];
}

void Vector::set(size_t index, Data value)
{
    if (index > m_size || index < 0)
    {
        throw std::out_of_range("Incorrect index");
    }

    m_dataStart[index] = value;
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
            newData[i] = m_dataStart[i];
        }
        if (m_dataAllocStart)
        {
            delete[] m_dataAllocStart;
        }
        m_capacity = newCapacity;
        m_dataAllocStart = newData;
        m_dataStart=m_dataAllocStart;
    }
    m_size = size;
}