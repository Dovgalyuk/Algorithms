#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <utility>
#include <vector>

using namespace std;

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector()
    {
    }

    // copy constructor
    Vector(const Vector &a)
        : data(a.data)
    {
    }

    // assignment operator
    Vector &operator=(const Vector &a)
    {
        data = a.data;
        return *this;
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        return data.at(index);
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        data.at(index) = move(value);
    }

    // Retrieves current vector size
    size_t size() const
    {
        return data.size();
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size)
    {
        data.resize(size);
    }

    typename vector<Data>::reference operator[](size_t index)
    {
        return data.at(index);
    }

    typename vector<Data>::const_reference operator[](size_t index) const
    {
        return data.at(index);
    }
private:
    // private data should be here
    vector<Data> data;
};

#endif
