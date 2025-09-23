#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
#include <stdexcept>

// Change it to desired type
typedef int Data;

class Array
{


public:
    // create array
    explicit Array(size_t size);

    // copy constructor
    Array(const Array& other);

    // assignment operator
    Array& operator=(const Array& other);

    // delete array, free memory
    ~Array();

    // returns specified array element
    Data get(size_t index) const;



    // sets the specified array element to the value
    void set(size_t index, Data value);

    // returns array size
    size_t size() const;

private:
    // private data should be here
    size_t size_;
    Data* data_;

};

#endif
