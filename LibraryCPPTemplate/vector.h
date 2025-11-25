#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>

const size_t INCREASE_SIZE = 2;

template <typename Data> class Vector
{
public:
    Vector()
    {
        size_v = 0;
        capacity_v = 1;
        arr_v = new Data[capacity_v]();
    }

    Vector(size_t size)
    {
        size_v = size;
        capacity_v = size;

        if (capacity_v < 1) 
        {
            capacity_v = 1;
        }
        
        arr_v = new Data[capacity_v]();
    }

    Vector(const Vector &a)
    {
        size_v = a.size_v;
        capacity_v = a.capacity_v;
        arr_v = new Data[capacity_v]();
        
        for (size_t i = 0; i < size_v; i++)
        {
            arr_v[i] = a.arr_v[i];
        }
    }

    Vector &operator=(const Vector &a)
    {
        if (this != &a)
        {
            delete[] arr_v;
            
            size_v = a.size_v;
            capacity_v = a.capacity_v;
            arr_v = new Data[capacity_v]();
            
            for (size_t i = 0; i < size_v; i++)
            {
                arr_v[i] = a.arr_v[i];
            }
        }

        return *this;
    }

    Data &operator[](size_t index)
    {
        return arr_v[index];
    }

    ~Vector()
    {
        delete[] arr_v;
    }

    Data get(size_t index) const
    {
        if(index >= size())
        {
            return Data();
        }

        return arr_v[index];
    }

    void set(size_t index, Data value)
    {
        if(index >= size())
        {
            return;
        }

        arr_v[index] = value;
    }

    size_t size() const
    {
        return size_v;
    }

    void resize(size_t size)
    {
        if(size > capacity_v)
        {
            size_t capacity = capacity_v;

            while (size > capacity)
            {
                capacity *= INCREASE_SIZE;
            }

            Data* arr = new Data[capacity]();

            for(size_t i = 0; i < size_v; i++)
            {
                arr[i] = arr_v[i];
            }

            delete[] arr_v;
            arr_v = arr;
            capacity_v = capacity;
        }
    
        size_v = size;
    }

    void push_back(Data value)
    {
        resize(size_v + 1);
        arr_v[size_v - 1] = value;
    }

    void erase(size_t index)
    {
        if (index >= size_v)
        {
            return;
        }
        
        for (size_t i = index; i < size_v - 1; i++)
        {
            arr_v[i] = arr_v[i + 1];
        }
        
        resize(size_v - 1);
    }

private:
    Data* arr_v;
    size_t size_v;
    size_t capacity_v;
};

#endif
