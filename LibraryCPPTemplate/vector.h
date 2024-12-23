#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <cstring>

template <typename Data>
class Vector {
public:
  // Default constructor
  Vector() : data_(nullptr), size_(0), capacity_(0) {}

  // Copy constructor
  Vector(const Vector& other) {
    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = new Data[capacity_];
    std::copy(other.data_, other.data_ + size_, data_);
  }

  // Move constructor
  Vector(Vector&& other) noexcept {
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  Vector(size_t size, const Data& initialValue = Data()) {
      capacity_ = size;
      size_ = size;
      data_ = new Data[capacity_];
      std::fill(data_, data_ + size_, initialValue);
  }

  // Destructor
  ~Vector() {
    delete[] data_;
  }

  // Copy assignment operator
  Vector& operator=(const Vector& other) {
    if (this != &other) {
      delete[] data_;
      capacity_ = other.capacity_;
      size_ = other.size_;
      data_ = new Data[capacity_];
      std::copy(other.data_, other.data_ + size_, data_);
    }
    return *this;
  }

  // Move assignment operator
  Vector& operator=(Vector&& other) noexcept {
    if (this != &other) {
      delete[] data_;
      data_ = other.data_;
      size_ = other.size_;
      capacity_ = other.capacity_;
      other.data_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }
    return *this;
  }

  // Access element at index
  Data& operator[](size_t index) {
    return data_[index];
  }

  // Access element at index (const version)
  const Data& operator[](size_t index) const {
    return data_[index];
  }

  Data get(size_t index) const {
    if (index >= size_) {
      throw std::out_of_range("Index out of range");
    }
    return data_[index];
  }

  void set(size_t index, const Data& value) {
    if (index >= size_) {
      throw std::out_of_range("Index out of range");
    }
    data_[index] = value;
  }

  // Get the size of the vector
  size_t size() const {
    return size_;
  }

  // Remove the last element from the vector
  void pop_back() {
    --size_;
  }

  // Reserve memory for a specific capacity
  void resize(size_t new_size) {
    if (new_size > capacity_) {
      capacity_ = new_size * 2;
      Data* new_data = new Data[capacity_];
      std::copy(data_, data_ + size_, new_data);
      delete[] data_;
      data_ = new_data;
    }
    size_ = new_size;
  }

  // Overloaded resize method with initial value
    void resize(size_t new_size, const Data& initialValue) {
        if (new_size > capacity_) {
            capacity_ = new_size * 2;
            Data* new_data = new Data[capacity_];
            std::copy(data_, data_ + size_, new_data);
            delete[] data_;
            data_ = new_data;
        }
        if (new_size > size_) {
            std::fill(data_ + size_, data_ + new_size, initialValue); // Fill new elements with initialValue
        }
        size_ = new_size;
    }

  void erase(size_t index) {
    if (index >= size_) {
      throw std::out_of_range("Index out of range");
    }


    // Use memmove to shift elements efficiently
    memmove(&data_[index], &data_[index + 1], (size_ - index - 1) * sizeof(Data));
    --size_;
  }

private:
  Data* data_;
  size_t size_;
  size_t capacity_;
};

#endif
