#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector()
    {
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        return Data();
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
    }

    // Retrieves current vector size
    size_t size() const
    {
        return 0;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size)
    {
    }

private:
    // private data should be here
};

#endif
