#pragma once

//Класс динамического массива с фиксированным размером
class Array {
private:
    int* data;
    int size;

public:
    Array(int n) {
        size = n;
        if (size > 0) {
            data = new int[size];
        } else {
            data = nullptr;
        }
    }

    ~Array() {
        delete[] data;
    }

    int getSize() const {
        return size;
    }

    int& operator[](int index) {
        return data[index];
    }
};
