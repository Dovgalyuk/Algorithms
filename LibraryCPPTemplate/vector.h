#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <cstddef>

template <typename T>
class Vector {
private:
    T* data;
    size_t current_size;
    size_t capacity;

public:
    T* begin() { return data; }
    T* end() { return data + current_size; }

    const T* begin() const { return data; }
    const T* end() const { return data + current_size; }

    Vector(size_t initial_capacity = 10) : current_size(0), capacity(initial_capacity) {
        data = new T[capacity];
    }

    Vector(std::initializer_list<T> init_list) : current_size(init_list.size()), capacity(init_list.size()) {
        data = new T[capacity];
        size_t i = 0;
        for (const T& element : init_list) {
            data[i++] = element;
        }
    }

     ~Vector() {
        for (size_t i = 0; i < current_size; ++i) {
             data[i].~T();
        }
        operator delete[](data);
    }

    size_t size() const { return current_size; }

    T& operator[](size_t index) {
        if (index >= current_size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= current_size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    void push_back(const T& value) {
        if (current_size == capacity) {
            resize(capacity * 2);
        }
        data[current_size++] = value;
    }

    void erase(size_t index) {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < current_size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --current_size;
    }

    void set(size_t index, const T& value) {
        if (index >= current_size) throw std::out_of_range("Index out of range");
        data[index] = value;
    }

    T& get(size_t index) { return data[index]; }
    const T& get(size_t index) const { return data[index]; }

    void resize(size_t new_capacity) {
    	T* new_data = new T[new_capacity];
    	std::copy(data, data + current_size, new_data);
    	delete[] data;
    	data = new_data;
    	capacity = new_capacity;
	}
};

#endif
