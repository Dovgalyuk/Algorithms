#pragma once

#include "vector.h"
#include <cstddef>
#include <stdexcept>

template <typename T>
class Stack {
private:
    Vector<T> data_;

public:
    bool empty() const { return data_.empty(); }
    std::size_t size() const { return data_.size(); }

    void push(const T& value)
    {
        data_.push_back(value);
    }

    T pop()
    {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        T result = data_.back();
        data_.pop_back();
        return result;
    }

    T& top()
    {
        return data_.back();
    }

    const T& top() const
    {
        return data_.back();
    }
};
