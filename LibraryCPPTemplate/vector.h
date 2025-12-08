#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>

using namespace std;

template <typename T> class Vector {
private:
  T *data_;
  size_t size_;
  size_t capacity_;

  void grow() {
    size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
    T *new_data = new T[new_cap];
    for (size_t i = 0; i < size_; i++) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_cap;
  }

public:
  Vector() : data_(nullptr), size_(0), capacity_(0) {}

  explicit Vector(size_t n, const T &val = T()) : size_(n), capacity_(n) {
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; i++) {
      data_[i] = val;
    }
  }

  Vector(const Vector &other) : size_(other.size_), capacity_(other.capacity_) {
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; i++) {
      data_[i] = other.data_[i];
    }
  }

  Vector &operator=(const Vector &other) {
    if (this != &other) {
      delete[] data_;
      size_ = other.size_;
      capacity_ = other.capacity_;
      data_ = new T[capacity_];
      for (size_t i = 0; i < size_; i++) {
        data_[i] = other.data_[i];
      }
    }
    return *this;
  }

  ~Vector() { delete[] data_; }

  void push_back(const T &val) {
    if (size_ >= capacity_) {
      grow();
    }
    data_[size_] = val;
    size_++;
  }

  T &operator[](size_t i) {
    if (i >= size_) {
      throw out_of_range("Vector index out of range");
    }
    return data_[i];
  }

  const T &operator[](size_t i) const {
    if (i >= size_) {
      throw out_of_range("Vector index out of range");
    }
    return data_[i];
  }

  size_t size() const { return size_; }

  void resize(size_t n, const T &val = T()) {
    if (n <= size_) {
      size_ = n;
    } else {
      if (n > capacity_) {
        T *new_data = new T[n];
        for (size_t i = 0; i < size_; i++) {
          new_data[i] = data_[i];
        }
        for (size_t i = size_; i < n; i++) {
          new_data[i] = val;
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = n;
      } else {
        for (size_t i = size_; i < n; i++) {
          data_[i] = val;
        }
      }
      size_ = n;
    }
  }

  void pop_back() {
    if (size_ == 0) {
      throw out_of_range("pop_back on empty vector");
    }
    size_--;
  }

  bool empty() const { return size_ == 0; }
};

#endif
