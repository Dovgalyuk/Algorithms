#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include <cmath>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define RESIZE_FACTOR 2

template <typename Data>
class Vector
{
public:
    Vector() : current_size(0), real_size(0), pointer(nullptr) {}

    Vector(const Vector &a) : current_size(a.current_size), real_size(a.real_size)
    {
        pointer = new Data[real_size];
        if (!pointer) throw std::bad_alloc();
        for (size_t i = 0; i < current_size; ++i) {
            pointer[i] = a.pointer[i];
        }
    }

    Vector &operator=(const Vector &a)
    {
        if (this != &a) {
            delete[] pointer;
            current_size = a.current_size;
            real_size = a.real_size;
            pointer = new Data[real_size];
            if (!pointer) throw std::bad_alloc();

            for (size_t i = 0; i < current_size; ++i)
                pointer[i] = a.pointer[i];
        }

        return *this;
    }

    ~Vector()
    {
        delete[] pointer;
    }

    Data get(size_t index) const
    {
        if (current_size <= index) throw std::out_of_range("The index is out of range");
        return pointer[index];
    }

    void set(size_t index, Data value)
    {
        if (current_size <= index) throw std::out_of_range("The index is out of range");
        pointer[index] = value;
    }

    size_t size() const
    {
        return current_size;
    }

    void resize(size_t new_size)
    {
        if (new_size > real_size) {
            size_t new_capacity = max(new_size, static_cast<size_t>(std::ceil(RESIZE_FACTOR * real_size)));

            Data *ptr = new Data[new_capacity];
            if (!ptr) throw std::bad_alloc();

            for (size_t i = 0; i < current_size; ++i) {
                ptr[i] = pointer[i]; 
            }

            delete[] pointer;

            pointer = ptr;
            real_size = new_capacity;
        }
        
        current_size = new_size; 
    }

    void resize(size_t new_size, Data value)
    {
        size_t old_size = current_size;
        resize(new_size);

        for (size_t i = old_size; i < current_size; ++i) {
            pointer[i] = value; 
        }
    }

    void push_back(Data value)
    {
        resize(current_size + 1);
        set(current_size - 1, value);
    }

    void pop_back()
    {
        if (current_size == 0) throw std::out_of_range("Cannot pop from an empty vector");
        current_size--;
    }

    Data &operator[](size_t index)
    {
        if (current_size <= index) throw std::out_of_range("The index is out of range");
        return pointer[index];
    }


private:
    size_t current_size;
    size_t real_size;
    Data *pointer;
};

#endif
