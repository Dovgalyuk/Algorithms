/*
����������� ��������� - ������������ ������ array � ������������ �������� (�� ����� �� ������)
��������� ������ ��������������� �������� ���������
�������� ��� ������� ��� ��������� ������� �� ��������� ������� � ������� �� �� ������� main.
������ ����� ����� � ����������, ������� ������ ����� ����������� � ��������� ��� ���������� �������.
�������� �������� ������� ��������� �� m, � �������� � ��������� �������� ��������� �� n. m � n ������ � ����������.
������ ����� ����� � ����������, ������� ������ ����� ����������� � ��������� ��� ���������� �������.
� ������� ����� ��������, ������� � ��� ����������� ������ ���� ���, � ������� �� �� �����.
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "array.h"

using namespace std;

void task1(Array *arr)
{
    size_t size;
    double n, m;
    cout << "������� ������ �������: ";
    cin >> size;
    /*int* arr_random = new int[size];*/
    arr = array_create(size);
    srand(time(NULL));
    cout << "��������� ������: " << endl;
    //�������� �������
    for (size_t i = 0; i < array_size(size); i++) {
        array_set(arr, i, rand());
        cout << array_get(arr, i) << " ";
    } cout << endl;
    cout << "������� m: ";
    cin >> m;
    cout << "������� n: ";
    cin >> n;
    //��������� �������
    for (size_t i = 0; i < array_size(size); i++) {
        if (array_get(arr, i) % 2 != 0) {
            array_get(arr, i) -= m;
        }
        if (i % 2 != 0) {
            array_get(arr, i) += n;
        }
    }
    //����� ������������� �������
    cout << "������������ ������: " << endl;
    for (size_t i = 0; i < array_size(size); i++) {
        cout << array_get(arr, i) << " ";
    }
}

void task2(Array *arr)
{
    size_t size;
    cout << "������� ������ �������: ";
    cin >> size;
    arr = array_create(size_t size);
    /*int* arr_random = new int[size];*/

    //�������� �������
    srand(time(NULL));
    cout << "��������� ������: " << endl;
    for (size_t i = 0; i < array_size(size); i++) {
        /*arr_random[i] = rand();*/
        array_set(arr, i, rand());
        cout << array_get(arr, i) << " ";
    } cout << endl;

    //��������� �������
    bool flag;
    for (size_t i = 0; i < array_size(size); i++) {
        for (size_t j = 0; j < array_size(size); j++) {
            flag = false;
            if (i != j and (array_set(arr, i) == array_set(arr, j))) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            cout << array_get(arr, i) << " ";
        }
    }
}

int main()
{
    Array *arr = NULL;

    task1(arr);
    array_delete(arr);

    task2(arr);
    array_delete(arr);
}
