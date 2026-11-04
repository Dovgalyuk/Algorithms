#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

template <typename Data> class Vector
{
public:
    Vector() : values(nullptr), count(0), capacity(0) {}

    Vector(const Vector &other) : Vector()
    {
        resize(other.count);
        for (size_t i = 0; i < count; ++i)
            values[i] = other.values[i];
    }

    Vector &operator=(const Vector &other)
    {
        if (this != &other)
        {
            Vector copy(other);
            swap(values, copy.values);
            swap(count, copy.count);
            swap(capacity, copy.capacity);
        }
        return *this;
    }

    ~Vector()
    {
        delete[] values;
    }

    Data get(size_t index) const
    {
        return index < count ? values[index] : Data();
    }

    void set(size_t index, Data value)
    {
        if (index < count)
            values[index] = value;
    }

    Data &operator[](size_t index)
    {
        if (index >= count)
            throw out_of_range("Vector index");
        return values[index];
    }

    const Data &operator[](size_t index) const
    {
        if (index >= count)
            throw out_of_range("Vector index");
        return values[index];
    }

    size_t size() const
    {
        return count;
    }

    void resize(size_t size)
    {
        if (size > capacity)
        {
            size_t new_capacity = capacity == 0 ? 1 : capacity;
            while (new_capacity < size)
            {
                if (new_capacity > numeric_limits<size_t>::max() / 2)
                {
                    new_capacity = size;
                    break;
                }
                new_capacity *= 2;
            }

            Data *data = new Data[new_capacity]{};
            try
            {
                for (size_t i = 0; i < count; ++i)
                    data[i] = values[i];
            }
            catch (...)
            {
                delete[] data;
                throw;
            }

            delete[] values;
            values = data;
            capacity = new_capacity;
        }

        for (size_t i = size; i < count; ++i)
            values[i] = Data();
        count = size;
    }

private:
    Data *values;
    size_t count;
    size_t capacity;
};

#endif
