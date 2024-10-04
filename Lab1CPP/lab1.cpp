#include <iostream>
#include <cstdlib>
#include <ctime>
#include "array.h"

using namespace std;

double calculateResist(Array* arr);
int findFrequent(Array* arr);

int main() {
	setlocale(LC_ALL, "RU");
	srand(static_cast<unsigned>(time(0)));

	int size;
	cout << "������� ������ �������: ";
	cin >> size;

	Array* arr = array_create(size);

	for (size_t i = 0; i < array_size(arr); ++i) {
		array_set(arr, i, rand() % 100 + 1); // ��������� ����� �� 1 �� 100
	}

	// ����� �������
	cout << "������: ";
	for (size_t i = 0; i < array_size(arr); ++i) {
		cout << array_get(arr, i) << " ";
	}
	cout << endl;

	// ���������� ������ ������������� ����
	double total = calculateResist(arr);
	cout << "����� ������������� ����: " << total << endl;

	// ����������� �������� ����� �������������� �����
	int mostFrequent = findFrequent(arr);
	cout << "�������� ����� ������������� �����: " << mostFrequent << endl;

	// �������� ������� � ������������ ������
	array_delete(arr);
}

double calculateResist(Array* arr) {
	double total = 0.0f;
	for (size_t i = 0; i < array_size(arr); ++i) {
		total += 1.0 / array_get(arr, i);
	}
	return 1.0 / total;
}

int findFrequent(Array* arr) {
	int maxCount = 0;
	int mostFrequet = array_get(arr, 0);
	for (size_t i = 0; i < array_size(arr); ++i) {
		int count = 0;
		for (size_t j = 0; j < array_size(arr); ++j) {
			if (array_get(arr, j) == array_get(arr, i)) {
				count++;
			}
		}
		maxCount = max(count, maxCount);
		mostFrequet = array_get(arr, i);
	}
	return mostFrequet;
}