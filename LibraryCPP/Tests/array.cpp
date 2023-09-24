#include "array.h"
#include <iostream>
using namespace std;


struct Array
{
public:
    Data* data;
    size_t sizeArr;


};

// create array
Array* array_create(size_t size)
{
    Array* arr = new Array;  //��������� ������ ��� ���������
    arr->sizeArr = size;          //��������� ������ ��� �������� ������� �������
    arr->data = new Data[size];  // ��������� ������ ��� �������� � �������

    return arr;
}

// delete array, free memory
void array_delete(Array* arr)
{
    delete[] arr->data;   //�������� �������
    delete arr;    //�������� ���������
}

// returns specified array element
Data array_get(const Array* arr, size_t index)
{
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value)
{
    arr->data[index] = value;  //���������� �������� � ������ �� ��������� �������


}

