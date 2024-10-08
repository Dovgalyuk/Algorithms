#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <cmath>
#include <stdexcept>

using namespace std;

template <typename Data> class Vector
{
public:
    // Creates empty vector
    Vector() : len(0), capacity(16), data(new Data[16])
    { }

    // Creates vector with default vales
    Vector(size_t size, Data default_value = Data())  // Data() represents the default value of type Data
    {
        len = capacity = size;
        data = new Data[capacity];

        for (size_t i = 0; i < len; i++) {
            data[i] = default_value;
        }
    }

    // copy constructor
    Vector(const Vector& a)
    {
        copy_vector(a);
    }

    // assignment operator
    Vector& operator=(const Vector& a)
    {
        // avoid self-assignment
        if (this != a)
            copy_vector(a);

        return *this;
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        len = capacity = 0;
        if (data) {
            delete[] data;
        }
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        if (index >= len || index < 0)
            throw out_of_range("Out of Range");

        return data[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if (index > len)
            throw out_of_range("Out of Range");

        data[index] = value;

        if (index == len)
            len++;
    }

    // Inserts element at the end
    void push(Data value)
    {
        if (len == capacity) {
            // increase capacity by 2 and resize the vector
            size_t new_capacity = (size_t)ceil(double(len) * 2);

            resize(new_capacity);
        }

        // set the value
        set(len, value);
    }

    // Deletes element at the end
    void pop() {
        if (!len) {
            throw "Empty container\n";
        }

        // decrease current length
        len--;

        // rezise if there are too many empty elements
        if (float(capacity) / float(len) > 2) {
            resize(len);
        }
    }

    // Retrieves current vector size
    size_t size() const
    {
        return len;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t new_size)
    {
        if (new_size > capacity) {
            size_t new_capacity = new_size * 2;
            Data* new_data = new Data[new_capacity];
            for (size_t i = 0; i < len; i++) {
                new_data[i] = data[i];
            }

            delete[] data;

            data = new_data;
            capacity = new_capacity;
        }

        len = new_size;
    }

private:
    // private data should be here
    size_t len;
    size_t capacity;
    Data* data;

    // Item copying algorithm for copy constructor and assigment operator
    void copy_vector(const Vector& a)
    {
        len = capacity = a.size();
        data = new Data[capacity];

        // copying existing elements
        for (size_t i = 0; i < len; i++) {
            data[i] = a.get(i);
        }
    }
};

#endif
