#include "array.h"

class Array
{
private:
    Data *data;
    size_t size;

public:
    Array(size_t size) : size(size)
    {
        data = new Data[size];
    }

    ~Array()
    {
        delete[] data;
    }

    Data get(size_t index) const
    {
        return data[index];
    }

    void set(size_t index, Data value)
    {
        data[index] = value;
    }

    size_t getSize() const
    {
        return size;
    }
};

Array *array_create(size_t size)
{
    if (size == 0)
        return nullptr;

    return new Array(size);
}

void array_delete(Array *arr)
{
    delete arr;
}

Data array_get(const Array *arr, size_t index)
{
    return arr->get(index);
}

void array_set(Array *arr, size_t index, Data value)
{
    arr->set(index, value);
}

size_t array_size(const Array *arr)
{
    return arr->getSize();
}