#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>
#include <cstddef>
using namespace std;
template <typename Data>
class Vector
{
public:
    Vector()
    {
        vector_size = 0;
        max_size = 1;
        data = new Data[max_size];
    }

    Vector(const Vector& a)
        : data(new Data[a.max_size]), vector_size(a.vector_size), max_size(a.max_size)
    {
        for (size_t i = 0; i < vector_size; i++)
        {
            data[i] = a.data[i];
        }
    }

    Vector& operator=(const Vector& a)
    {
        if (this == &a)
        {
            return *this;
        }

        delete[] data;

        vector_size = a.vector_size;
        max_size = a.max_size;
        data = new Data[max_size];

        for (size_t i = 0; i < vector_size; i++)
        {
            data[i] = a.data[i];
        }

        return *this;
    }

    ~Vector()
    {
        delete[] data;
    }

    Data get(size_t index) const
    {
        if (index < vector_size)
            return data[index];
        else
            throw std::out_of_range("Index out of range");
    }

    void set(size_t index, Data value)
    {
        if (index < vector_size)
            data[index] = value;
        else
            throw std::out_of_range("Index out of range");
    }

    void erase(size_t index)
    {
        if (index >= vector_size)
            throw std::out_of_range("Index out of range");

        for (size_t i = index; i < vector_size - 1; ++i)
        {
            data[i] = data[i + 1];
        }

        vector_size--;
    }
    size_t size() const
    {
        return vector_size;
    }

    void resize(size_t size)
    {
        if (size <= max_size)
        {
            vector_size = size;
            return;
        }

        size_t _max_size = size * 2;
        Data* new_data = new Data[_max_size];

        for (size_t i = 0; i < vector_size; i++)
        {
            new_data[i] = data[i];
        }


        for (size_t i = vector_size; i < _max_size; ++i)
        {
            new_data[i] = Data();
        }

        delete[] data;
        data = new_data;
        max_size = _max_size;
        vector_size = size;
    }

private:
    Data* data;
    size_t vector_size;
    size_t max_size;
};


#endif
