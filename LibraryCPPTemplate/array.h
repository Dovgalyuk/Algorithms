#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
#include <stdexcept>
#include <algorithm>

template<typename T>
class Array {
public:
    explicit Array(size_t size) : size_(size) {  // �����������
        if (size == 0) {
            data_ = nullptr;
        }
        else {
            data_ = new T[size]();
        }
    }

    ~Array() {  // ����������
        delete[] data_;
    }

    Array(const Array& other) : size_(other.size_) {  // ���������� �����������
        if (size_ == 0) {
            data_ = nullptr;
        }
        else {
            data_ = new T[size_];
            std::copy(other.data_, other.data_ + size_, data_);
        }
    }

    Array& operator=(const Array& other) {  // �������� ������������
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            if (size_ == 0) {
                data_ = nullptr;
            }
            else {
                data_ = new T[size_];
                std::copy(other.data_, other.data_ + size_, data_);
            }
        }
        return *this;
    }

    size_t size() const { return size_; }

    T& operator[](size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

private:
    T* data_;
    size_t size_;
};

#endif // ARRAY_H