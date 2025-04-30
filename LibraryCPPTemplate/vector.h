#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <cstddef>
#include <initializer_list>

template <typename T>
class Vector {
private:
    T* data;
    size_t current_size;
    size_t capacity;

public:
    Vector(size_t initial_capacity = 10)
        : data(new T[initial_capacity]), current_size(0), capacity(initial_capacity) {}

    Vector(std::initializer_list<T> init_list)
        : data(new T[init_list.size()]), current_size(init_list.size()), capacity(init_list.size()) {
        size_t i = 0;
        for (const T& value : init_list)
            data[i++] = value;
    }

    ~Vector() { delete[] data; }

    void push_back(const T& value) {
        if (current_size == capacity)
            resize(capacity * 2);
        data[current_size++] = value;
    }

    void erase(size_t index) {
        if (index >= current_size) throw std::out_of_range("Index out of range");
        for (size_t i = index; i < current_size - 1; ++i)
            data[i] = data[i + 1];
        --current_size;
    }

    void set(size_t index, const T& value) {
        if (index >= current_size) throw std::out_of_range("Index out of range");
        data[index] = value;
    }

    T get(size_t index) const {
        if (index >= current_size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    void resize(size_t new_size) {
        if (new_size > capacity) {
            T* new_data = new T[new_size];
            for (size_t i = 0; i < current_size; ++i)
                new_data[i] = data[i];
            delete[] data;
            data = new_data;
            capacity = new_size;
        }
        current_size = new_size;
    }

    T& operator[](size_t index) {
        if (index >= current_size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= current_size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    size_t size() const { return current_size; }

    T* begin() { return data; }
    T* end() { return data + current_size; }

    const T* begin() const { return data; }
    const T* end() const { return data + current_size; }
};

#endif
