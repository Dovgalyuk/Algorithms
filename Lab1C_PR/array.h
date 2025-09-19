#ifndef ARRAY_H
#define ARRAY_H

#include <stdexcept>

using namespace std;

class Array {
private:
    int* data;
    int size;

public:
    Array(int s) {
        if (s <= 0)
            throw invalid_argument("������ ������ ���� �������������!");

        size = s;
        data = new int[size]; // ��������� ������.
        for (int i = 0; i < size; i++)
            data[i] = 0;
    }

    ~Array() { delete[] data; } // ������� ������.

    int getSize() const { return size; }

    int& get(int index) {
        if (index < 0 || index >= size)
            throw out_of_range("������ ��� ������!");

        return data[index];
    }

    const int& get(int index) const {
        if (index < 0 || index >= size)
            throw out_of_range("������ ��� ������!");

        return data[index];
    }

    void set(int index, int value) { get(index) = value; }

    void fillFrom(const int* source) {
        for (int i = 0; i < size; i++)
            data[i] = source[i];
    }
};

#endif