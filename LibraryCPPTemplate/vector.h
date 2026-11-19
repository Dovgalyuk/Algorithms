#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>

template <typename Data>
class Vector
{
public:
    // Creates vector
    Vector()
    {
        data = nullptr;
        v_size = 0;
        capacity = 0;
    }

    // copy constructor
    Vector(const Vector &a)
    {
        v_size = a.v_size;
        capacity = a.capacity;

        if (capacity == 0)
            data = nullptr;
        else
        {
            data = new Data[capacity];
            for (size_t i = 0; i < v_size; i++)
            {
                data[i] = a.data[i];
            }
        }
    }

    // assignment operator
    Vector &operator=(const Vector &a)
    {
        if (this == &a)
            return *this;

        Vector temp(a);
        swap(temp);

        return *this;
    }

    void swap(Vector &a)
    {
        Data *temp_data = data;
        data = a.data;
        a.data = temp_data;

        size_t temp_size = v_size;
        v_size = a.v_size;
        a.v_size = temp_size;

        size_t temp_capacity = capacity;
        capacity = a.capacity;
        a.capacity = temp_capacity;
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete[] data;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        if (index >= v_size)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if (index >= v_size)
            throw std::out_of_range("Index out of range");
        data[index] = value;
        return;
    }

    // Retrieves current vector size
    size_t size() const
    {
        return v_size;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size)
    {
        if (size > capacity)
        {
            size_t new_capacity = capacity;

            if (new_capacity == 0)
                new_capacity = 1;

            while (new_capacity < size)
                new_capacity *= 2;

            Data *new_data = new Data[new_capacity];

            for (size_t i = 0; i < v_size; i++)
                new_data[i] = data[i];

            delete[] data;

            data = new_data;
            capacity = new_capacity;
        }

        v_size = size;
    }

private:
    Data *data;
    size_t v_size;
    size_t capacity;
};

#endif
