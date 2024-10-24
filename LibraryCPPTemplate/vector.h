#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>

template <typename Data>
class Vector {
public:
    
    Vector() : arr(new Data[1]), size_v(0), capacity(1) {}

    Vector(size_t q){
        arr = new Data[q];
        size_v = 0;
        capacity = q;
        for (size_t i = 0; i < q; i++)
            push(Data());
    }

    Vector(const Vector& a) : size_v(a.size_v), capacity(a.capacity) {
        arr = new Data[capacity];
        for (size_t i = 0; i < size_v; ++i) {
            arr[i] = a.arr[i];
        }
    }

    Vector& operator=(const Vector& a) {
        if (this == &a) return *this;

        delete[] arr;
        size_v = a.size_v;
        capacity = a.capacity;
        arr = new Data[capacity];

        for (size_t i = 0; i < size_v; ++i) {
            arr[i] = a.arr[i];
        }
        return *this;
    }

    Data& operator[](size_t index) {
        if (index >= size_v) {
            return arr[0];
        }
        return arr[index];
    }

    ~Vector() {
        delete[] arr;
        arr = nullptr;
    }

    Data get(size_t index) const {
        if (index >= size_v) {
            return Data();
        }
        return arr[index];
    }

    void set(size_t index, Data value) {
        if (index < size_v) {
            arr[index] = value;
        }
    }

    size_t size() const {
        return size_v;
    }

    void push(Data value) {
        if (size_v >= capacity) {
            resize(capacity * 2);
        }
        arr[size_v++] = value;
    }

    Data pop() {
        if (size_v > 0) {
            return arr[--size_v];
        }
        return Data();
    }

    void resize(size_t new_size) {
        if (new_size < size_v) {
            size_v = new_size;
        }
        if (new_size > capacity) {
            Data* new_ptr = new Data[new_size];
            for (size_t i = 0; i < size_v; ++i) {
                new_ptr[i] = arr[i];
            }
            delete[] arr;
            arr = new_ptr;
            capacity = new_size;
        }
    }

private:
    Data* arr;
    size_t size_v;
    size_t capacity;
};

#endif