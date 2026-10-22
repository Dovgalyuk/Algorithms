#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename Data>
class Vector
{
public:
    // Creates an empty vector
    Vector()
        : length(0), capacity(0), items(nullptr)
    {
    }

    // Creates an independent copy
    Vector(const Vector &a)
        : length(a.length), capacity(a.length),
          items(copyItems(a.items, a.length, a.length))
    {
    }

    // Replaces the contents with a copy
    Vector &operator=(const Vector &a)
    {
        if (this != &a)
        {
            Vector copy(a);
            std::swap(length, copy.length);
            std::swap(capacity, copy.capacity);
            std::swap(items, copy.items);
        }

        return *this;
    }

    // Frees the allocated memory
    ~Vector()
    {
        delete[] items;
    }

    // Returns an element
    Data get(size_t index) const
    {
        if (index >= length)
        {
            throw std::out_of_range("Invalid vector index");
        }

        return items[index];
    }

    // Changes an element
    void set(size_t index, Data value)
    {
        if (index >= length)
        {
            throw std::out_of_range("Invalid vector index");
        }

        items[index] = value;
    }

    // Returns the number of elements
    size_t size() const
    {
        return length;
    }

    // Changes the number of elements
    void resize(size_t size)
    {
        if (size > capacity)
        {
            size_t new_capacity = capacity == 0 ? 1 : capacity * 2;

            if (new_capacity < size)
            {
                new_capacity = size;
            }

            Data *new_items = copyItems(items, length, new_capacity);

            delete[] items;
            items = new_items;
            capacity = new_capacity;
        }
        else
        {
            for (size_t i = length; i < size; i++)
            {
                items[i] = Data();
            }
        }

        length = size;
    }

private:
    size_t length;
    size_t capacity;
    Data *items;

    // Allocates memory and copies existing elements
    static Data *copyItems(const Data *source,
                           size_t count,
                           size_t new_capacity)
    {
        Data *result = new Data[new_capacity]();

        try
        {
            for (size_t i = 0; i < count; i++)
            {
                result[i] = source[i];
            }
        }
        catch (...)
        {
            delete[] result;
            throw;
        }

        return result;
    }
};

#endif