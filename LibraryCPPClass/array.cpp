#include "array.h"

using namespace std;

Array::Array(size_t size) : m_arrData(new Data[size]()), m_arrSize(size) // initialization list: 1. dynamic array with "size" allocating memory with "new" 2. array size 
{
    for(size_t i = 0; i < m_arrSize; i++) // initialization array by 0
    {
        m_arrData[i] = 0;
    }
}

Array::Array(const Array &a) : m_arrData(new Data[a.m_arrSize]()), m_arrSize(a.m_arrSize) // initialization list: 1. new array 2. new array size
{
    for (size_t i = 0; i < m_arrSize; ++i) // copy elements from array 'a' to new array
    {
        m_arrData[i] = a.m_arrData[i];
    }
}

Array &Array::operator=(const Array &a)
{
    if (this == &a) // check that the object assigning to itself
    {
        return *this;
    }

    delete[] m_arrData;

    m_arrSize = a.m_arrSize; // assignment of new size
    m_arrData = new Data[m_arrSize]; // allocate memory for array with new size

    for (size_t i = 0; i < m_arrSize; ++i) // copy elemets from array 'a'
    {
        m_arrData[i] = a.m_arrData[i];
    }

    return *this;
}

Array::~Array() // destructor
{
    delete[] m_arrData;
}

Data Array::get(size_t index) const 
{
    if (index >= m_arrSize)
    {
        throw out_of_range("Error: index is out of range");
    }

    return m_arrData[index];
}

void Array::set(size_t index, Data value)
{
    if (index >= m_arrSize)
    {
        throw out_of_range("Error: index is out of range");
    }

    m_arrData[index] = value;
}

size_t Array::size() const
{
    return m_arrSize;
}
