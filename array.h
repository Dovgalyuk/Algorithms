#pragma once
#include <stdexcept>

template<typename T>
class array {
private:
    T* data;
    size_t sz;

public:
    explicit array(size_t size) : sz(size) {
        data = new T[sz];
    }

    ~array() {
        delete[] data;
    }

    array(const array&) = delete;
    array& operator=(const array&) = delete;

    T& operator[](size_t index) {
        if (index >= sz) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= sz) throw std::out_of_range("Index out of range");
        return data[index];
    }

    size_t size() const { return sz; }
};
