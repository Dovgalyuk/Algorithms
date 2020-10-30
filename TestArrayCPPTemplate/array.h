#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename Data> class Array
{
public:
    // create array
    Array(size_t size)
    {
        elem = new Data[size];
        sized = size;
    
    }

    // delete array, free memory
    ~Array()
    {
        delete[] elem;
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return elem[index];
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
        elem[index] = value;
    }

    // returns array size
    size_t size() const
    {

        return sized;
    }

private:
    Data* elem;
    size_t sized;
    // private data should be here
};

#endif
