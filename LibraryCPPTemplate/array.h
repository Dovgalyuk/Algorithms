#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename Data> class Array
{
public:
    // create array
    Array(size_t size)
    {
    }

    // delete array, free memory
    ~Array()
    {
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return Data(0);
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
    }

    // returns array size
    size_t size() const
    {
        return 0;
    }

private:
    // private data should be here
};

#endif
