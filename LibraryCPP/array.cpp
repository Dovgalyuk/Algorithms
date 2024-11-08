#include "array.h"


// ��������� �������
struct Array {
    Data* elements;
    size_t size;
};

// �������� �������
Array* array_create(size_t size) {
    Array* arr = new Array;
    arr->elements = new Data[size];
    arr->size = size;
    return arr;
}

void array_delete(Array* arr)
{
    delete[] arr->elements;
    delete arr;
}

// ����������� ���������� �������� �������
Data array_get(const Array* arr, size_t index) {
    return arr->elements[index];
}

// ���������� �������� ���������� �������� � �������
void array_set(Array* arr, size_t index, Data value) {
    arr->elements[index] = value;
}

// ������� ������ �������
size_t array_size(const Array* arr)
{
    return arr->size;
}
