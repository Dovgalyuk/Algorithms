#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename Data> class Array
{
public:
    // create array
    Array(size_t size): s(size), array(new Data[size]) {}

    // delete array, free memory
    ~Array()
    {
        delete[] array;
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return array[index];
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
        array[index] = value;
    }

    // returns array size
    size_t size() const
    {
        return s;
    }

private:
    Data* array;
    size_t s;
};

#endif
