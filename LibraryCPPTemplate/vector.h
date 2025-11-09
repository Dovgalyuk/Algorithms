#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <initializer_list>
#include <concepts>
#include <stdexcept>
#include <utility>
#include "concepts.h"
#include "iterator.h"

template <std::copyable Data> 
class Vector
{
public:
    Vector() : data_(nullptr), size_(0), capacity_(0)
    {}

    explicit Vector(std::size_t size) 
        : data_(static_cast<Data*>(::operator new(size * sizeof(Data)))), size_(size), capacity_(size)  
    {
        std::uninitialized_value_construct_n(data_, size_);
    }

    Vector(std::size_t size, const Data& defaultValue) : Vector(size) {
        std::uninitialized_fill_n(data_, size_, defaultValue);
    }

    Vector(const Vector &a) 
        : data_(static_cast<Data*>(::operator new(a.size_ * sizeof(Data)))), size_(a.size_), capacity_(a.capacity_)
    {
        std::uninitialized_copy(a.begin(), a.end(), data_);
    }

    Vector(Vector&& a) noexcept {
        data_ = a.data_;
        size_ = a.size_;
        capacity_ = a.capacity_;

        a.data_ = nullptr;
        a.size_ = 0;
        a.capacity_ = 0;
    }

    Vector(std::initializer_list<Data> list) : 
        data_(static_cast<Data*>(::operator new(list.size() * sizeof(Data)))), size_(list.size()), capacity_(list.size())
    {
        std::uninitialized_copy(list.begin(), list.end(), data_);
    }

    Vector &operator=(const Vector &a)
    {
        if (&a != this) {
            if (a.size_ <= capacity_) {
                Data* newEnd = std::copy(a.begin(), a.end(), data_);
                std::destroy(newEnd, data_ + size_);
            }
            else {
                Data* newData = static_cast<Data*>(::operator new(a.size_ * sizeof(Data)));
                try {
                    std::uninitialized_copy(a.begin(), a.end(), newData);
                }
                catch (...) {
                    ::operator delete(newData);
                    throw;
                }

                std::destroy(begin(), end());
                ::operator delete(data_);

                data_ = newData;
                size_ = a.size_;
                capacity_ = a.capacity_;
            }
        }

        return *this;
    }

    Vector& operator=(Vector&& a) {
        if (&a != this) {
            std::destroy(begin(), end());
            ::operator delete(data_);

            data_ = a.data_;
            capacity_ = a.capacity_;
            size_ = a.size_;

            a.data_ = nullptr;
            a.size_ = 0;
            a.capacity_ = 0;
        }

        return *this;
    }

    Data& operator[](std::size_t index) {
        return data_[index];
    }

    const Data& operator[](std::size_t index) const {
        return data_[index];
    }

    Data& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Vector::at: index out of range");
        }
        return data_[index];
    }

    const Data& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Vector::at: index out of range");
        }
        return data_[index];
    }

    ~Vector()
    {
        clear();
        if (data_) {
            ::operator delete(data_);
        }
    }

    // alias for vector test
    Data get(std::size_t index) const
    {
        return this->at(index);
    }

    void set(std::size_t index, Data value)
    {
        this->at(index) = value;
    }

    std::size_t size() const
    {
        return size_;
    }

    std::size_t capacity() const {
        return capacity_;
    }

    Data& front() {
        return data_[0];
    }

    Data& back() {
        return data_[size_ - 1];
    }

    const Data& back() const {
        return data_[size_ - 1];
    }

    void push_back(const Data& value) {
        if (size_ == capacity_) {
            recalculateCapacity();
        }

        std::construct_at(data_ + size_, value);
        ++size_;
    }

    void push_back(Data&& value) {
        if (size_ == capacity_) {
            recalculateCapacity();
        }

        std::construct_at(data_ + size_, std::move(value));
        ++size_;
    }

    void pop_back() {
        if (size_ == 0) return;

        std::destroy(data_ + size_ - 1, data_ + size_);
        --size_;
    }

    template<class... Args>
    void emplace_back(Args&&... args) {
        if (size_ == capacity_) {
            recalculateCapacity();
        }
        std::construct_at(data_ + size_, std::forward<decltype(args)>(args)...);
        
        ++size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(std::size_t size) // simple implement
    {
        if (size > capacity_) {
            std::size_t newCapacity = capacity_ == 0 ? 1 : capacity_;
            while (newCapacity < size) {
                newCapacity *= 2;
            }

            this->reserve(newCapacity);
        }

        size_ = size;
    }

    void reserve(std::size_t capacity) {
        if (capacity > capacity_) {
            reallocate(capacity);
        }
    }

    void clear() {
        std::destroy(data_, data_ + size_);
        size_ = 0;
    }

    // simple resize with std rules;
    void stdResize(std::size_t size) {
        if (size < size_) {
            std::destroy(data_ + size, data_ + size_);
            size_ = size;
        }
        else if (size > size_) {
            if (size > capacity_) {
                reserve(size);
            }

            std::uninitialized_value_construct_n(end(), size - size_);
            size_ = size;
        }
    }

    void resize(std::size_t size, const Data& defaultValue) {
        if (size < size_) {
            std::destroy(data_ + size, data_ + size_);
            size_ = size;
        }
        else if (size > size_) {
            if (size > capacity_) {
                reserve(size);
            }

            std::uninitialized_fill_n(end(), size - size_, defaultValue);
            size_ = size;
        }
    }

    void shrink_to_fit() {
        if (size_ == capacity_) return;

        if (size_ == 0) {
            std::destroy(begin(), end());
            ::operator delete(data_);
            data_ = nullptr;
            capacity_ = 0;
        }
        else {
            reallocate(size_);
        }
    }

    iterator<Data> begin() noexcept {
        return iterator(data_);
    }

    iterator<Data> end() noexcept {
        return iterator(data_ + size_);
    }

    iterator<const Data> begin() const noexcept {
        return iterator<const Data>(data_);
    }

    iterator<const Data> end() const noexcept {
        return iterator<const Data>(data_ + size_);
    }

    iterator<const Data> cbegin() const noexcept {
        return iterator<const Data>(data_);
    }

    iterator<const Data> cend() const noexcept {
        return iterator<const Data>(data_ + size_);
    }

private:
    void recalculateCapacity() {
        const std::size_t newCapacity = (capacity_ > 0) ? capacity_ * 2 : 1;
        reserve(newCapacity);
    }

    void reallocate(std::size_t size) {
        Data* newData = static_cast<Data*>(::operator new(size * sizeof(Data)));
        try {
            if constexpr (std::is_nothrow_move_constructible_v<Data>) {
                std::uninitialized_move(begin(), end(), newData);
            }
            else {
                std::uninitialized_copy(begin(), end(), newData);
            }
        }
        catch (...) {
            ::operator delete(newData);
            throw;
        }

        std::destroy(begin(), end());
        ::operator delete(data_);

        data_ = newData;
        capacity_ = size;
    }

    Data* data_;
    std::size_t size_;
    std::size_t capacity_;
};

#endif
