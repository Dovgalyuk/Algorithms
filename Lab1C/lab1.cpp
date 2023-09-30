#include <iostream>
#include "array.h"
#include <time.h> 
#include <random>

using namespace std;

Array* create() {
    size_t size;
    Array* arr = NULL; // ������� ������ ��� ��������� �������
    cout << "what about size of array? " << endl;
    while (true) {
        cin >> size; // ������ ������ �������

        if (cin.fail()) { // ���� ���� �� ������
            cout << "Incorrect input" << endl;
            cin.clear(); // ������� ���� ������
            cin.ignore(32767, '\n'); // ������� ����� �����
        }
        else {            
            arr = array_create(size); // ������� ������ ���������� �������
            for (size_t i = 0; i < size; i++) {
                int j = rand() % 2; // ���������� ��������� �����: 0 ��� 1
                if (j == 0) {
                    array_set(arr, i, (rand() % 100) * -1); // ���� ����� 0, �� ���������� ������������� �����
                }
                else {
                    array_set(arr, i, (rand() % 100)); // ���� ����� 1, �� ���������� ������������� �����
                }
            }
        }
        break;
    }
    return arr; // ���������� ��������� ������
}

void first(Array* arr) {
    size_t size = array_size(arr); // �������� ������ �������
    Data elem = 0;
    Data sum = 0;
    float ariph = 0;
    Data count = 0;
    for (size_t i = 0; i < size; i++) {
        elem = array_get(arr, i); // �������� ������� ������� �� �������
        sum += elem; // ��������� ��� �������� �������
        count++; // ����������� �������
    }

    ariph = ((float)sum / (float)count); // ��������� ������� ��������������

    cout << "The arithmetic mean of this array" << endl << ariph << endl; // ������� ������� ��������������
    
}

void second(Array* arr) {
    size_t size = array_size(arr); // �������� ������ �������
    Data elem = 0;
    Data elemsec = 0;

    for (size_t i = 0; i < size; i++) {
        elem = array_get(arr, i); // �������� ������� ������� �� �������
        int count = 1;
        for (size_t j = 0; j < size; j++) {
            elemsec = array_get(arr, j); // �������� ������ ������� ������� �� �������
            if (elem == elemsec && i != j) { // ���� �������� �����, �� ������� �� ���������
                count++; // ����������� �������        
            }
        }
        if (count == 2) { // ���� count ����� 2, �� ������� ����������� ���� ���
            cout << elem << " "; // ������� �������      
        }
        array_set(arr, i, -1000); // �������� ������� �� -1000
    }
}


void print(const Array* arr) {
    size_t size = array_size(arr); // �������� ������ �������
    cout << "Look on your array: " << endl;
    for (size_t i = 0; i < size; i++) {
        cout << array_get(arr, i) << " "; // ������� �������� �������
    }
    cout << endl;
}

int main()
{
    srand(time(NULL)); // �������������� ��������� ��������� �����
    Array* arr = NULL;

    cout << "task1" << endl;
    arr = create(); // ������� ������
    print(arr); // ������� ������ �� �����
    first(arr); // ��������� ������ �������
    array_delete(arr); // ������� ������

    cout << "task2" << endl;
    arr = create(); // ������� ������
    print(arr); // ������� ������ �� �����
    second(arr); // ��������� ������ ������� 
}