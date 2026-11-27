#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <limits>   
#include <memory>   
#include <utility>  

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector()
    {
    }

    // copy constructor
    Vector(const Vector &a)
    {
        resize(a.size());
        for (size_t i = 0; i < length; ++i)
            data[i] = a.data[i];
    }

    // assignment operator
    Vector &operator=(const Vector &a)
    {
        if (this != &a)
        {
            Vector copy(a);
            swap(copy);
        }
        return *this;
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        return data[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        data[index] = std::move(value);
    }

    // Retrieves current vector size
    size_t size() const
    {
        return length;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size)
    {
        if (size > capacity)
        {
            size_t newCapacity = size;
            if (capacity <= std::numeric_limits<size_t>::max() / 2
                && capacity * 2 > size)
                newCapacity = capacity * 2;

            std::unique_ptr<Data[]> buffer(new Data[newCapacity]{});
            for (size_t i = 0; i < length; ++i)
                buffer[i] = data[i];
            data.swap(buffer);
            capacity = newCapacity;
        }

        for (size_t i = size; i < length; ++i)
            data[i] = Data{};
        length = size;
    }
    Data &operator[](size_t index) { return data[index]; }
    const Data &operator[](size_t index) const { return data[index]; }

    void swap(Vector &a) noexcept
    {
        data.swap(a.data);
        std::swap(length, a.length);
        std::swap(capacity, a.capacity);
    }


private:
    // private data should be here
    std::unique_ptr<Data[]> data;
    size_t length = 0;
    size_t capacity = 0;
};

#endif
