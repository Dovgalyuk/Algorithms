#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

// Change it to desired type
typedef size_t Data;

class Vector
{
public:
    // Creates vector
    Vector();

    // copy constructor
    Vector(const Vector &a);

    // assignment operator
    Vector &operator=(const Vector &a);

    // Deletes vector structure and internal data
    ~Vector();

    // Retrieves vector element with the specified index
    Data get(size_t index) const;

    // Sets vector element with the specified index
    void set(size_t index, Data value);

    // Retrieves current vector size
    size_t size() const;

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size);

private:
    // private data should be here
    Data* elements;
    size_t capacity_value;
    size_t size_value;
};

#endif
