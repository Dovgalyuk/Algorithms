#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
#include <stdexcept>
#include <iostream>

typedef int Data;

class Array
{
public:
    explicit Array(size_t size);

    // copy constructor
    Array(const Array &a);

    // assignment operator
    Array &operator=(const Array &a);

    // delete array, free memory
    ~Array();

    // returns specified array element
    Data get(size_t index) const;

    // sets the specified array element to the value
    void set(size_t index, Data value);

    // returns array size
    size_t size() const;

private:
    size_t m_size;
    Data* m_data;
};

#endif