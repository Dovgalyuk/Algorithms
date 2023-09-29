#include <iostream>
#include "array.h"
#include <ctime> 
#include <vector> 

using namespace std;

void count(Array *arr, Data value, int &znach) { //���������� ����������� ���������� ������
	size_t size = array_size(arr);
	for (size_t i = 0; i < size; i++) {
		if (array_get(arr, i) == value) {
			znach += 1;
		}
	}
}

void conclusion(Array *arr) { //����� �� ����� �������
	size_t size = array_size(arr);
	for (size_t i = 0; i < size; i++) {
		cout << array_get(arr, i) << " ";
	}
}


void task1(Array *arr)
{
	size_t size = array_size(arr);
	for (size_t i = 0; i < size; i++) {
		array_set(arr, i, 2 + rand() % 4); //���������� ������� ������� �� 2 �� 5
	}
	cout << "Foreign language grades:" << endl;
	conclusion(arr);
	cout << endl;
	for (Data i = 2; i < 6; i++) {
		int znach = 0;
		count(arr, i, znach);
		cout << "Quantity " << i << ": " << znach << " " << endl;
	}


}

void task2(Array *arr)
{
	size_t size = array_size(arr);
	for (size_t i = 0; i < size; i++) {//���������� ������� ������� �� 0 �� 99
		array_set(arr, i, rand() % 100);
	}
	cout << "Values in array:" << endl;
	conclusion(arr);
	cout << endl;
	vector<Data> replays(0);
	cout << "Elements that appear exactly twice:" << endl;
	for (size_t i = 0; i < size; i++) { //���������� ��������� ������� ����������� ����� ��� ����
		Data a = array_get(arr, i);
		int quantity = 1;
		for (size_t j = 0; j < size; j++) {
			if ((a == array_get(arr, j)) && (i != j)) {
				quantity += 1;
			}
		}
		if (quantity == 2) {
			bool flag = true;
			for (size_t k = 0; k < replays.size(); k++) { //�������� �� ���������� �� ��� ��� ����� 
				if (a == replays[k]) {
					flag = false;
				}
			}
			if (flag) {
				replays.push_back(a);
				cout << a << " ";
			}
		}
	}
}

void examination(size_t &size) { //�������� �� ��������� ����
	while (true) {
		cin >> size;
		if (!cin.fail()) {
			break;
		}
		else {
			cout << "Enter again:" << endl;
			cin.clear();
			cin.ignore(32767, '\n');
		}
	}
}



int main()
{
	srand(time(NULL));
	Array *arr = NULL;
	size_t size;
	cout << "Enter array length:";
	examination(size);
	arr = array_create(size);
	/* Create array here */
	task1(arr);
	array_delete(arr);
	/* Create another array here */
	cout << "Enter array length:";
	examination(size);
	arr = array_create(size);
	task2(arr);
	array_delete(arr);
}
