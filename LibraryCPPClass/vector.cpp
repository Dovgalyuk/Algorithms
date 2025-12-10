#include "vector.h"
#include <algorithm> 
#include <cstring>   
#include <stdexcept>

Vector::Vector() : m_data(nullptr), m_size(0), m_capacity(0)
{
}

void Vector::copy_from(const Vector& a)
{
    if (a.m_size == 0) {
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
        return;
    }
    m_data = new Data[a.m_size];
    for (size_t i = 0; i < a.m_size; ++i)
        m_data[i] = a.m_data[i];
    m_size = a.m_size;
    m_capacity = a.m_size;
}

Vector::Vector(const Vector& a)
    : m_data(nullptr), m_size(0), m_capacity(0)
{
    copy_from(a);
}

Vector& Vector::operator=(const Vector& a)
{
    if (this == &a) return *this;
    delete[] m_data;
    copy_from(a);
    return *this;
}

Vector::~Vector()
{
    delete[] m_data;
}

Data Vector::get(size_t index) const
{
    if (index >= m_size) throw std::out_of_range("Vector::get index out of range");
    return m_data[index];
}

void Vector::set(size_t index, Data value)
{
    if (index >= m_size) throw std::out_of_range("Vector::set index out of range");
    m_data[index] = value;
}

size_t Vector::size() const
{
    return m_size;
}

void Vector::ensure_capacity(size_t min_capacity)
{
    if (m_capacity >= min_capacity) return;
    size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity;
    while (new_capacity < min_capacity) new_capacity *= 2;
    Data* new_data = new Data[new_capacity];
    for (size_t i = 0; i < m_size; ++i) new_data[i] = m_data[i];
    delete[] m_data;
    m_data = new_data;
    m_capacity = new_capacity;
}

void Vector::resize(size_t new_size)
{
    if (new_size <= m_capacity) {
        for (size_t i = m_size; i < new_size; ++i) m_data[i] = Data();
        m_size = new_size;
        return;
    }
    ensure_capacity(new_size);
    for (size_t i = m_size; i < new_size; ++i) m_data[i] = Data();
    m_size = new_size;
}