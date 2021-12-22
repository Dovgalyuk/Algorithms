#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename Data> class Array
{
public:
    // create array
    Array(size_t size)
    {
        array_size=size;
        point = new Data[size];
    }

    // delete array, free memory
    ~Array()
    {
        delete[] point;
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return point[index];
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
        point[index]=value;
    }

    // returns array size
    size_t size() const
    {
        return array_size;
    }

private:
    // private data should be here
    size_t array_size;
    Data* point;
};

#endif
