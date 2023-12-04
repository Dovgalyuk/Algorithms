/*
����������� ��������� - ������������ ������ array � ������������ �������� (�� ����� �� ������)
��������� ������ ��������������� �������� ���������
�������� ��� ������� ��� ��������� ������� �� ��������� ������� � ������� �� �� ������� main.
������ ����� ����� � ����������, ������� ������ ����� ����������� � ��������� ��� ���������� �������.
�������� �������� ������� ��������� �� m, � �������� � ��������� �������� ��������� �� n. m � n ������ � ����������.
������ ����� ����� � ����������, ������� ������ ����� ����������� � ��������� ��� ���������� �������.
� ������� ����� ��������, ������� � ��� ����������� ������ ���� ���, � ������� �� �� �����.
*/
#include "array.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


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
    for (size_t i = 0; i < array_size(arr); i++) {
        array_set(arr, i, rand());
        cout << array_get(arr, i) << " ";
    } cout << endl;
    cout << "������� m: ";
    cin >> m;
    cout << "������� n: ";
    cin >> n;
    //��������� �������
    for (size_t i = 0; i < array_size(arr); i++) {
        if (array_get(arr, i) % 2 != 0) {
            array_set(arr, i, value - m);
        }
        if (i % 2 != 0) {
            array_set(arr, i, value + n);
        }
    }
    //����� ������������� �������
    cout << "������������ ������: " << endl;
    for (size_t i = 0; i < array_size(arr); i++) {
        cout << array_get(arr, i) << " ";
    }
}

void task2(Array *arr)
{
    size_t size;
    cout << endl << "������� ������ �������: ";
    cin >> size;
    arr = array_create(size);
    /*int* arr_random = new int[size];*/

    //�������� �������
    srand(time(NULL));
    /*cout << "��������� ������: " << endl;*/
    for (size_t i = 0; i < array_size(arr); i++) {
        /*arr_random[i] = rand();*/
        array_set(arr, i, rand());
        /*cout << array_get(arr, i) << " ";*/
    } cout << endl;

    //��������� �������
    bool flag;
    for (size_t i = 0; i < array_size(arr); i++) {
        for (size_t j = 0; j < array_size(arr); j++) {
            flag = false;
            if (i != j and (array_get(arr, i) == array_get(arr, j))) {
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
    setlocale(LC_ALL, "Ru");
    Array* arr = NULL;

    task1(arr);
    array_delete(arr);

    task2(arr);
    array_delete(arr);
}
