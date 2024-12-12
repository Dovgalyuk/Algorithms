#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>

template <typename Data>
class Vector {
public:
    // Creates vector
    Vector() : data(nullptr), capacity(0), sizee(0) {}

    Vector(size_t size) : data(new Data[size]), capacity(size), sizee(0) {}

    // Copy constructor
    Vector(const Vector &vec)
        : data(new Data[vec.capacity]), capacity(vec.capacity), sizee(vec.sizee) {
        for (size_t i = 0; i < vec.sizee; i++) {
            data[i] = vec.data[i];
        }
    }

    // Assignment operator
    Vector &operator=(const Vector &vec) {
        if (this == &vec) {
            return *this;
        }

        delete[] data;

        capacity = vec.capacity;
        sizee = vec.sizee;
        data = new Data[capacity];
        for (size_t i = 0; i < sizee; i++) {
            data[i] = vec.data[i];
        }

        return *this;
    }

    // Deletes vector structure and internal data
    ~Vector() {
        delete[] data;
    }

    // Retrieves vector element with the specified index
    Data &get(size_t index) const {
        if (index >= sizee) {
            throw std::out_of_range("out of range");
        }
        return data[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value) {
        if (index >= sizee) {
            throw std::out_of_range("out of range set");
        }
        data[index] = value;
    }

    // Retrieves current vector size
    size_t size() const {
        return sizee;
    }

    // Change capacity
    void resize(size_t new_size) {
        if (new_size > capacity) {
            size_t new_capacity = new_size * 2;
            Data *newData = new Data[new_capacity];
            for (size_t i = 0; i < sizee; ++i) {
                newData[i] = data[i];
            }

            delete[] data;
            data = newData;
            capacity = new_capacity;
        }
        sizee = new_size;
    }

private:
    Data *data;
    size_t capacity;
    size_t sizee;
};

#endif // VECTOR_TEMPLATE_H
