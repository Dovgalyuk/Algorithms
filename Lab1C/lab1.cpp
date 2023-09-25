#include <iostream>
#include "array.h"

using namespace std;

void create(Array*& arr) { //������� �������� � ���������� ������� ���������� �������
	size_t size; //������ �������
	cout << "Enter array's size: ";
	while (true) { //��������� ��������� �����
		cin >> size;
		if (!cin.fail()) { //���� ��� ������ � �����, �� ������� �� �����, ����� ���������� �����
			break;
		}
		else {
			cout << "Incorrect input" << endl;
			cin.clear(); //���������� cin � ������� ����� ������ 
			cin.ignore(32767, '\n'); //� ������� �������� ����������� ����� �� �������� ������
		}
	}
	arr = array_create(size); //��������� ������ ��� �������
	for (size_t i = 0; i < size; i++) { //������� ������� 
		array_set(arr, i, rand() % 100); //����������� ��������� ����� �� 0 �� 100
	}
}

void print(const Array* arr) { //������� ������ �������
	size_t size = array_size(arr); //����� � ���������� ������ �������, ����� ����� 1 ��� ��� �����, � �� �������� ������ ��� � for
	cout << "Array is: ";
	for (size_t i = 0; i < size; i++) { //�������
		cout << array_get(arr, i) << " "; //������ �������
	}
	cout << endl;
}

void task1(Array* arr)
{
	size_t size = array_size(arr); //������ ������ �������
	print(arr); //�������� ������, ����� ����� ���� ��������� ���������
	int counter_two = 0, counter_five = 0; //��� ��������
	for (size_t i = 0; i < size; i++) { //������� ���������
		Data elem = array_get(arr, i); //�.�. �� ��������� � 2 if, �� ����� � ����������, ����� ����� ������ 1 ���
		if (elem % 2 == 0) {
			counter_two++;
		}
		if (elem % 10 == 5) {
			counter_five++;
		}
	}
	cout << "Elements are even: " << counter_two << endl;
	cout << "Elements ending with 5" << counter_five << endl;
}

void task2(Array* arr)
{
	size_t size = array_size(arr); //������ ������ �������
	print(arr); //�������� ������
	int total_count = 0; //�������, ��� ��������, ������� �� ������� �� �� ���� ������ �������
	for (size_t i = 0; i < size; i++) { //������� �������
		Data elem = array_get(arr, i); //������ �������, ������� ����� ���������
		size_t local_count = 0; //�������, ���� ������� �� ������� �� ������ 1 ������� �������
		for (size_t j = 0; j < size; j++) { //������� ������� ������ ���
			if (elem % array_get(arr, j) != 0) { //���������, ���� ������� �� ������� �� ������ ������� �������, ��������� � local_count 1
				local_count += 1;
			}
		}
		if (local_count == size - 1) { //���� ������� �� ������� �� �� ���� ������ ������� �������, �� �� �� ������� �� (���-�� ���� ���������)-(��� �������)
			total_count += 1;
		}
	}
	cout << total_count;
}

int main()
{
	srand(time(NULL));
	Array* arr = NULL;
	cout << "Task 1" << endl;
	create(arr);
	task1(arr);
	array_delete(arr);
	cout << "Task 1" << endl;
	create(arr);
	task2(arr);
	array_delete(arr);
}
