#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <algorithm>

template <typename Data>
class Vector
{
public:
    Vector() : data_(new Data[1]), size_(0), max_size_(1) {}

    template <typename T>
    Vector(const Vector<T>& a) : data_(new Data[a.max_size_]), size_(a.size_), max_size_(a.max_size_) {
        std::copy(a.data_, a.data_ + a.size_, data_);
    }

    template <typename T>
    Vector& operator=(const Vector<T>& a) {
    if ((void*)this != (void*)&a) {
        delete[] data_;
        data_ = new Data[a.max_size_];
        size_ = a.size_;
        max_size_ = a.max_size_;
        std::copy(a.data_, a.data_ + a.size_, data_);
    }
    return *this;
}


    ~Vector() {
        delete[] data_;
        data_ = nullptr;
    }

    Data get(size_t index) const {
        if (size_ <= index) throw "Error";
        return data_[index];
    }

    void set(size_t index, Data value) {
        if (size_ <= index) throw "Error";
        data_[index] = value;
    }

    size_t size() const { return size_; }

    void resize(size_t size) {
        if (size >= max_size_) {
           size_t new_max_size = size * 2;
           Data* tmp = new Data[new_max_size];
           for (size_t i = 0; i < size_; i++) {
               tmp[i] = data_[i];
          }
           // Проверка на nullptr перед удалением
           if (data_ != nullptr) {
               delete[] data_;
           }
           data_ = tmp;
           max_size_ = new_max_size;
           }
         size_ = size;
    }

    /*void push_back(Data value) {
        while (size_ >= max_size_) {
            size_t new_max_size = max_size_ * 2;
            Data* new_data = new Data[new_max_size];
            for (size_t i = 0; i < size_; i++) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            max_size_ = new_max_size;
        }
        data_[size_] = value;
        size_++;
    }*/


private:
    Data* data_;
    size_t size_;
    size_t max_size_;
};

#endif
