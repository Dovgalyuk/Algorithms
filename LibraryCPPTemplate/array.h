#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

#include <cstddef>

template <typename Data> class Array
{
public:
    // create array
    explicit Array(size_t size)
    {
        length = size;
        items = new Data[length];
    }

    // copy constructor
    Array(const Array &a)
    {
        length = a.length;
        items = new Data[length];

        for (size_t i = 0; i < length; i++)
        {
            items[i] = a.items[i];
        }
    }

    // assignment operator
    Array &operator=(const Array &a)
    {
        if (this == &a)
        {
            return *this;
        }

        delete[] items;

        length = a.length;
        items = new Data[length];

        for (size_t i = 0; i < length; i++)
        {
            items[i] = a.items[i];
        }

        return *this;
    }

    // delete array, free memory
    ~Array()
    {
        delete[] items;
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return items[index];
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
        items[index] = value;
    }

    // returns array size
    size_t size() const
    {
        return length;
    }

private:
    size_t length;
    Data *items;
};

#endif