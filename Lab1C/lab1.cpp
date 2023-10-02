#include "array.h"
#include <iostream>

using namespace std;

void task1(Array *arr)
{
    size_t size = array_size(arr);

    size_t maxElement = array_get(arr, 0);//������������� ������������� �������� ������ ��������� �������
    for (size_t i = 0; i < size; i += 2)//�������� � �������� � �������� 0 � ��� �� ������ �������� (+2)
    {
        size_t currentElement = array_get(arr, i);//��������� �������� �������� �������
        if (currentElement > maxElement)
        {
            maxElement = currentElement;//����� ������������ �������
        }
    }

    cout << "������������ ������� ����� ��������� � ������ ��������: " << maxElement << endl;
}

void task2(Array* arr)
{
    size_t size = array_size(arr);
    cout << "������� �������� [a,b]:";
    size_t a;
    size_t b;
    cin >> a >> b;

    size_t zero = 0; //���������� ��������� ���������

    //����������� ��������� ��������� � ������ �������
    for (size_t i = 0; i < size; ++i)
    {
        int currentElement = array_get(arr, i);

        //��������, ��������� �� ������� � ��������� [a, b]
        if (currentElement < a || currentElement > b)
        {
            //������� �� ��������� � ���������, ������������� ��� �������� � 0
            array_set(arr, zero, size_t());
        }
        else
        {
            //������� ��������� � ���������, ���������� ��� � ������ �������
            array_set(arr, zero, currentElement);
            zero++;
        }
    }

    //���������� ���������� ������� ������
    for (size_t i = zero; i < size; ++i)
    {
        array_set(arr, i, size_t());
    }
}


void CreateArray(Array* arr) {
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; i++)
        array_set(arr, i, rand());
}

int main()
{
    setlocale (LC_ALL,"ru");
    srand((unsigned int)time(NULL)); //������������� ���������� ��������� �����
    Array* arr = nullptr;
    size_t size;

    //task1
    cout << "������� ������ �������: ";
    cin >> size;
    arr = array_create(size);
    CreateArray(arr);
    cout << "��������������� ������: ";
    for (size_t i = 0; i < size; ++i)
    {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;
    task1(arr);
    array_delete(arr);

    //task2
    cout << "������� ������ ������� 2: ";
    cin >> size;
    arr = array_create(size);
    CreateArray(arr);
    cout << "��������������� ������: ";
    for (size_t i = 0; i < size; ++i)
    {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;

    task2(arr);
    // ������� ���������
    cout << "��������� ������: ";
    for (size_t i = 0; i < array_size(arr); ++i)
    {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;
    array_delete(arr);
}
