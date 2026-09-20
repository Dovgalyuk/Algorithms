#pragma once

// Класс динамического массива с фиксированным размером
class Array {
private:
    int* data;
    int size;

public:
    // Конструктор: выделяет память под n элементов
    Array(int n) {
        size = n;
        if (size > 0) {
            data = new int[size];
        } else {
            data = nullptr;
        }
    }

    // Деструктор: освобождает память
    ~Array() {
        delete[] data;
    }

    int getSize() const {
        return size;
    }

    // Перегрузка квадратных скобок для доступа по индексу: arr[i]
    int& operator[](int index) {
        return data[index];
    }
};
