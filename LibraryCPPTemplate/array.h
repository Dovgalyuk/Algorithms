#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
#include <utility>


template <typename Data>
class Array
{
private:

    Data* data;
    size_t array_size;


    void copy(const Array& other)
    {
        array_size = other.array_size;
        data = new Data[array_size];

        for (size_t i = 0; i < array_size; i++)
        {
            data[i] = other.data[i];
        }
    }


public:

    Array(size_t size)
    {
        array_size = size;
        data = new Data[array_size];
    }


    Array(const Array& other)
    {
        copy(other);
    }


    Array& operator=(const Array& other)
    {
        if (this != &other)
        {
            Array temp(other);

            std::swap(data, temp.data);
            std::swap(array_size, temp.array_size);
        }

        return *this;
    }


    ~Array()
    {
        delete[] data;
    }


    void set(size_t index, Data value)
    {
        data[index] = value;
    }


    Data get(size_t index) const
    {
        return data[index];
    }


    size_t size() const
    {
        return array_size;
    }
};


#endif
