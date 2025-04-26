#include <stdexcept>

template <typename T>
class Vector {
private:
    T* data;
    size_t sz;
    size_t capacity;

    void grow() {
        size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < sz; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    Vector() : data(nullptr), sz(0), capacity(0) {}

    ~Vector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (sz == capacity) {
            grow();
        }
        data[sz++] = value;
    }

    void clear() {
        sz = 0;
    }

    void resize(size_t new_size) {
        if (new_size > capacity) {
            size_t new_capacity = new_size;
            T* new_data = new T[new_capacity];
            for (size_t i = 0; i < sz; ++i) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
        sz = new_size;
    }

    void set(size_t index, const T& value) {
        if (index >= sz) throw std::out_of_range("Index out of bounds");
        data[index] = value;
    }

    T& get(size_t index) {
        if (index >= sz) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    const T& get(size_t index) const {
        if (index >= sz) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    size_t size() const {
        return sz;
    }
};
