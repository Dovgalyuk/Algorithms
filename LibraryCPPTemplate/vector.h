// Файл с шаблонным вектором

#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector()
    { 
        arr = new Data[0];
    }
    
    // copy constructor
    Vector(const Vector &a) {
        if (a.arr != nullptr) {
            size_v = a.size_v;
            capacity = a.capacity;
            arr = new Data[capacity];

            for (size_t i = 0; i < a.size(); ++i) {
                set(i, a.get(i));
            }
        }
    }

    // assignment operator
    Vector &operator=(const Vector &a)
    {
        if (this == &a) return *this;
        if (a.arr != nullptr) {
            if (arr != nullptr) {
                delete[] arr;
            }

            size_v = a.size_v;
            capacity = a.capacity;
            arr = new Data[capacity];

            for (size_t i = 0; i < a.size(); ++i) {
                set(i, a.get(i));
            }
        }
        return *this;
    }

    Data &operator[](size_t index){
        if (sizeof(arr) == 0) return arr[index];
        Data default_data;
        return default_data;
    }

    // Deletes vector structure and internal data
    ~Vector()
    { 
        if (arr != nullptr) delete[] arr;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        if (sizeof(arr) != 0) return arr[index];
        return Data();
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    { 
        if (arr != nullptr && index <= size_v) arr[index] = value;
    }

    // Retrieves current vector size
    size_t size() const
    {
        if (arr != nullptr) return size_v;
        return (size_t)0;
    }

    void push(Data value) {
        if (sizeof(arr) == 0 || size_v >= capacity) {
            size_t new_cap = 0;
            if (capacity == 0)
                new_cap = 1;
            else
                new_cap = capacity * 2;
        
            resize(new_cap);
        }
        set(size_v, value);
        size_v++;
    }

    Data pop() {
        if (size_v > 0) {
            return get(--size_v);
        }
        return Data();
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size) {
        if (size > capacity) {
            size_t ncap = size * 2;
            Data* new_ptr = new Data[ncap];
            for (size_t i = 0; i < size_v; ++i) {
                new_ptr[i] = arr[i];
            }

            delete[] arr;
            arr = new_ptr;
            capacity = ncap;
        }
        //size_v = size;
    }

private:
    // private data should be here
    Data *arr = nullptr;
    size_t size_v = 0;
    size_t capacity = 0;
};

#endif