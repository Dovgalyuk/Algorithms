#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector()
    {
        size_1 = res_size = 0;
        data = (Data*)res_size;
    }

    // copy constructor
    //Vector(const Vector &a)
    //{
        // implement or disable this function
    //}

    // assignment operator
    //Vector &operator=(const Vector &a)
    //{
        // implement or disable this function
       // return *this;
   // }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete[] data;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        return data[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if (index < size_1) {
            data[index] = value;
        }
        else {
            resize(index + 1);
            data[index] = value;
        }
    }

    // Retrieves current vector size
    size_t size() const
    {
        return size_1;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size)
    {
        if (size <= res_size) {
            size_1 = size;
        }
        else {
            size_t new_size = size * 2;
            Data* new_data = (Data*)new_size;
            for (size_t i = 0; i < size_1; i++) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            size_1 = size;
            res_size = new_size;
        }
    }

private:
    size_t size_1;
    size_t res_size;
    Data* data;
    // private data should be here
};

#endif
