#include "array.h"

struct Array
{
    Data* data;  // ���������� ��������� �� Data ������ ������ Data
    size_t size;
};

// �������� �������
Array array_create(size_t size)
{
    Array newArr;
    newArr.data = new Data[size];
    newArr.size = size;
    return newArr;
}

// �������� �������, ������������ ������
void array_delete(Array arr)
{
    delete[] arr.data;
}

// ���������� ��������� ������� �������
Data array_get(const Array arr, size_t index)
{
    if (index < arr.size) {
        return arr.data[index];
    }
    else {
        // ��������� ������ ������ �� ������� �������
        return Data(); // ���������� �������� �� ��������� ��� ���� Data
    }
}

// ������������� �������� ���������� �������� �������
void array_set(Array arr, size_t index, Data value)
{
    if (index < arr.size) {
        arr.data[index] = value;
    }
    else {
        // ��������� ������ ������ �� ������� �������
    }
}

// ���������� ������ �������
size_t array_size(const Array arr)
{
    return arr.size;
}
