#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <algorithm>

template <typename Data>
class Vector {
public:
    
    Vector() {
        arr = new Data[1];
        size_v = 0;
        capacity = 1;
    }

    Vector(size_t q, Data value){
        arr = new Data[q];
        size_v = 0;
        capacity = q;
        for (size_t i = 0; i < q; i++)
            push(value);
    }

    Vector(const Vector& a) {
        size_v = a.size_v; 
        capacity = a.capacity;
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

    const Data& operator[](size_t index) const {
        if (index >= size_v) {
            return arr[0];
        }
        return arr[index];
    }

    ~Vector() {
        delete[] arr;
        arr = nullptr;
    }

    Data get(size_t index) {
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

    void resize(size_t new_size) {
        if (new_size > capacity) {
            capacity = new_size * 2;
            Data* new_ptr = new Data[capacity];
            for (size_t i = 0; i < size_v; ++i) {
                new_ptr[i] = arr[i];
            }
            delete[] arr;
            arr = new_ptr;
        }
        size_v = new_size;
    }

    void push(Data value) {
        if (size_v >= capacity) {
            resize(size_v + 1);
            size_v--;
        }
        arr[size_v++] = value;
    }

    Data pop() {
        if (size_v > 0) {
            return arr[--size_v];
        }
        return Data();
    }

    Data pop_front() {
        if (size_v > 0) {
            Data temp = arr[0];
            erase(0);
            return temp;
        }
        return Data();
    }

    Data erase(size_t index) {
        if (size_v == 0 || index > size_v)
            return Data();

        Data temp = arr[index];
        for (size_t i = index; i < size_v - 1; i++) {
            arr[i] = arr[i + 1];
        }

        if(size_v - 1 < capacity)
            resize(size_v - 1);

        return temp;
    }

    void clear() {
        size_v = 0;
        capacity = 0;
        delete[] arr;
        arr = nullptr;
    }

    Vector<Data> reverse(size_t start, size_t end) {
        while (start < end) {
            std::swap(arr[start], arr[end]);
            ++start;
            --end;
        }

        return *this;
    }

private:
    Data* arr;
    size_t size_v;
    size_t capacity;
};

#endif