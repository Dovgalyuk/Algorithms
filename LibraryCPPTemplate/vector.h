#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include <algorithm>

template <typename Data>
class Vector
{
private:
    Data* data_;
    size_t size_;
    size_t capacity_;

    void reallocate(size_t new_capacity) {
        if (new_capacity < size_) {
            new_capacity = size_;
        }

        Data* new_data = new Data[new_capacity];

        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    // Creates empty vector
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    // Creates vector with specified size
    Vector(size_t initial_size) : data_(nullptr), size_(0), capacity_(0) {
        if (initial_size > 0) {
            resize(initial_size);
        }
    }

    // Creates vector with specified size and initial value
    Vector(size_t initial_size, const Data& initial_value) : data_(nullptr), size_(0), capacity_(0) {
        if (initial_size > 0) {
            resize(initial_size);
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = initial_value;
            }
        }
    }

    // copy constructor
    Vector(const Vector& a) : data_(nullptr), size_(0), capacity_(0) {
        if (a.size_ > 0) {
            data_ = new Data[a.capacity_];
            capacity_ = a.capacity_;
            size_ = a.size_;
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = a.data_[i];
            }
        }
    }

    // assignment operator
    Vector& operator=(const Vector& a) {
        if (this != &a) {
            Vector temp(a);
            swap(temp);
        }
        return *this;
    }

    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    // Deletes vector structure and internal data
    ~Vector() {
        delete[] data_;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }
        return data_[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value) {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }
        data_[index] = value;
    }

    // Retrieves current vector size
    size_t size() const {
        return size_;
    }

    // Changes the vector size (may increase or decrease)
    void resize(size_t new_size) {
        if (new_size > capacity_) {
            size_t new_capacity = new_size * 2;
            if (new_capacity < 4) new_capacity = 4;
            reallocate(new_capacity);
        }

        if (new_size > size_) {
            for (size_t i = size_; i < new_size; ++i) {
                data_[i] = Data();
            }
        }

        size_ = new_size;
    }
    Data& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }
        return data_[index];
    }
    const Data& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }
        return data_[index];
    }
    void push_back(const Data& value) {
        if (size_ >= capacity_) {
            reallocate(capacity_ == 0 ? 4 : capacity_ * 2);
        }
        data_[size_++] = value;
    }
    void insert(size_t index, const Data& value) {
        if (index > size_) {
            throw std::out_of_range("Vector index out of range");
        }

        if (size_ >= capacity_) {
            reallocate(capacity_ == 0 ? 4 : capacity_ * 2);
        }

        for (size_t i = size_; i > index; --i) {
            data_[i] = data_[i - 1];
        }

        data_[index] = value;
        ++size_;
    }
    void erase(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }

        for (size_t i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }

        --size_;
    }

    void clear() {
        size_ = 0;
    }

    bool empty() const {
        return size_ == 0;
    }

    size_t capacity() const {
        return capacity_;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            reallocate(new_capacity);
        }
    }
};
#endif