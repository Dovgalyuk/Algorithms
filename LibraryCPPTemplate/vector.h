#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <utility>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector() : data(nullptr), length(0), capacity(0) {}

    // copy constructor
    Vector(const Vector &a) : data(new Data[a.length]{}), length(a.length), capacity(a.length)
    { for (size_t i = 0; i < length; i++) data[i] = a.data[i]; }

    // assignment operator
    Vector &operator=(const Vector &a)
    { if (this != &a) { Vector copy(a); swap(copy); } return *this; }

    // Deletes vector structure and internal data
    ~Vector() { delete[] data; }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        return data[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value) { data[index] = value; }

    // Retrieves current vector size
    size_t size() const
    {
        return length;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size)
    {
        if (size > capacity) {
            size_t new_capacity = capacity ? capacity : 1;
            while (new_capacity < size) new_capacity *= 2;
            Data *new_data = new Data[new_capacity]{};
            for (size_t i = 0; i < length; i++) new_data[i] = data[i];
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
        for (size_t i = length; i < size; i++) data[i] = Data();
        length = size;
    }

private:
    void swap(Vector &a) { std::swap(data, a.data); std::swap(length, a.length); std::swap(capacity, a.capacity); }
    Data *data;
    size_t length;
    size_t capacity;
};

#endif
