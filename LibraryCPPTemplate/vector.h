// Файл с шаблонным вектором

#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector()
    { 
        arr = new Data();
    }

    // copy constructor
    Vector(const Vector &a)
    {
    }

    // assignment operator
    Vector &operator=(const Vector &a)
    {
        return *this;
    }

    // Deletes vector structure and internal data
    ~Vector()
    { 
        if (arr != nullptr) delete[] arr;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        if (arr != nullptr) return arr[index];
        return (Data)0;
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    { 
        if (arr != nullptr) {
            if (index <= size_v)
                arr[index] = value;
            else
                resize(index);
        }
    }

    // Retrieves current vector size
    size_t size() const
    {
        if (arr != nullptr) return size_v;
        return (size_t)0;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size)
    {
    }

private:
    // private data should be here
    Data *arr = nullptr;
    size_t size_v = 0;
    size_t capacity = 0;
};

#endif
