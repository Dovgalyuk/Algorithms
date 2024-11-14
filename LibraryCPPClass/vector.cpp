#include "vector.h"
#include <stdexcept>

// Конструктор по умолчанию
Vector::Vector() : data_(nullptr), capacity_(0), size_(0) {}

// Конструктор копирования
Vector::Vector(const Vector &a) : data_(new Data[a.capacity_]), capacity_(a.capacity_), size_(a.size_) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = a.data_[i];
    }
}

// Оператор присваивания
Vector &Vector::operator=(const Vector &a) {
    if (this != &a) {
        delete[] data_;
        capacity_ = a.capacity_;
        size_ = a.size_;
        data_ = new Data[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = a.data_[i];
        }
    }
    return *this;
}

// Деструктор
Vector::~Vector() {
    delete[] data_;
}

// Получение элемента по индексу
Data Vector::get(size_t index) const {
    if (index >= size_) throw std::out_of_range("Index out of range");
    return data_[index];
}

// Установка значения элемента по индексу
void Vector::set(size_t index, Data value) {
    if (index >= size_) throw std::out_of_range("Index out of range");
    data_[index] = value;
}

// Получение текущего размера вектора
size_t Vector::size() const {
    return size_;
}

// Изменение размера вектора
void Vector::resize(size_t new_size) {
    if (new_size > capacity_) {
        size_t new_capacity = new_size * 2;
        Data *new_data = new Data[new_capacity];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }
    size_ = new_size;
}
