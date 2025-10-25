#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>

template <typename Data> class Vector
{
private:
    // private data should be here
    const size_t grow_constant = 2;
    Data* data;
    size_t size_v;
    size_t new_capacity;
   

public:
    // Creates vector
    Vector() : data(nullptr), size_v(0), new_capacity(grow_constant)
    {
        data = new Data[new_capacity];
    }   

    // copy constructor
    Vector(const Vector& a) :size_v(a.size_v), new_capacity(a.new_capacity)
    {
        data = new Data[new_capacity];
        for (size_t i = 0; i < size_v; i++)
        {
            data[i] = a.data[i];
        }
    }

    // assignment operator
    Vector&operator=(const Vector& other)
    {
        if (this != &other)
        {
            Data* new_data = new Data[other.new_capacity];
            for (size_t i = 0; i < other.size_v; i++)
            {
                new_data[i] = other.data[i];
            }
            delete[] data;
            data = new_data;
            size_v = other.size_v;
            new_capacity = other.new_capacity;
        }
        return *this;
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete[] data;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        if (index >= size_v)
        {
            throw std::out_of_range("ERROR: index out of range");
        }
        else
        {
            return data[index];
        }

    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if (index >= size_v)
        {
            throw std::out_of_range("ERROR: index out of range");
        }
        else
        {
            data[index] = value;
        }
    }

    // Retrieves current vector size
    size_t size() const
    {
        return size_v;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size)
    {
        //Если требуемый размер нужен меньше 
        if (size <= size_v)
        {
            size_v = size;
        }
        //Если требуемый размер нужен больше
        else 
        {    
            if (new_capacity < size)
            {
                while (new_capacity < size)
                {
                    new_capacity *= grow_constant;
                }
                Data* old_data = data;
                data = new Data[new_capacity];
                for (size_t i = 0; i < size_v; i++)
                {
                    data[i] = old_data[i];
                }
                delete[] old_data;
            }
            size_v = size;
           
        }
    }


};

#endif
