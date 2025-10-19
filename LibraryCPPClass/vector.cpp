#include "vector.h"
#include <stdexcept>

Vector::Vector():size_v(0),new_capacity(0), data(new Data [2])
{
    new_capacity = size_v * grow_constant;
    data = new Data[new_capacity];
    for (size_t i = 0; i < size_v; i++)
    {
        data[i] = Data();
    }
}

Vector::Vector(const Vector &a) :size_v(a.size_v),new_capacity(0)
{
    new_capacity = size_v * grow_constant;
    data = new Data[new_capacity];
    for (size_t i = 0; i < size_v; i++)
    {
        data[i] = a.data[i];
    }
}

Vector &Vector::operator=(const Vector &other)
{
    if (this != &other)
    {
        delete[] data;
        size_v = other.size();
        new_capacity = size_v * grow_constant;
        data = new Data[new_capacity];
        for (size_t i = 0; i < size_v; i++)
        {
            data[i] = other.data[i];
        }
    }
    return *this;
}

Vector::~Vector()
{
    delete[] data;
}

Data Vector::get(size_t index) const
{
    if (index >= size_v)
    {
    throw std::out_of_range("ERROR: index out of range");
    }
    else
    {
        return data[index];
    }
    
}

void Vector::set(size_t index, Data value)
{
    if (index >= size_v)
    {
        throw std::out_of_range("ERROR: index out of range");
    }
    else
    {
        data[index] = value;
    }
}

size_t Vector::size() const
{
    return size_v;
}

void Vector::resize(size_t size)
{
    
     if (size <= size_v)
    {
        size_v = size;
    }
     else if (size > size_v)
     {
         size_t old_size = size_v;
         if (new_capacity < size)
         {
            
             Data* old_data = data;
             new_capacity = size * grow_constant;
             data = new Data[new_capacity];
             for (size_t i = 0; i < old_size; i++)
             {
                 data[i] = old_data[i];
             }
             delete[] old_data;
         }

       
         size_v = size;

         for (size_t i = old_size; i < size_v; i++)
         {
             data[i] = Data();
         }
     }
}
