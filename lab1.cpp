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

using namespace std;

class DynamicArray {
public:
	int size;
	int* arr;

	DynamicArray(int s) {
		size = s;
		arr = new int[size];
	}

	void fillArrayRandomly() {
		for (int i = 0; i < size; i++) {
			arr[i] = rand() % 100 + 1; // ��������� ������ ���������� ������� �� 1 �� 100
		}
	}

	void printArray() {
		for (int i = 0; i < size; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}

	void increaseOddIndicesByN(int n) {
		for (int i = 0; i < size; i++) {
			if (i % 2 != 0) {
				arr[i] += n;
			}
		}
	}

	void decreaseOddElementsByM(int m) {
		for (int i = 0; i < size; i++) {
			if (arr[i] % 2 != 0) {
				arr[i] -= m;
			}
		}
	}

	void findUniqueElements() {
		for (int i = 0; i < size; i++) {
			int count = 0;
			for (int j = 0; j < size; j++) {
				if (i != j && arr[i] == arr[j]) {
					count++;
				}
			}
			if (count == 0) {
				cout << arr[i] << " ";
			}
		}
	}

	~DynamicArray() {
		delete[] arr;
	}
};

int main() {
	setlocale(LC_ALL, "Ru");
	int size, n, m;
	srand(time(NULL)); // ������������� ������� rand()

	cout << "������� ������ �������: ";
	cin >> size;

	DynamicArray array(size);
	array.fillArrayRandomly();

	cout << "��������� ������: ";
	array.printArray();

	cout << "������� �������� n: ";
	cin >> n;
	array.increaseOddIndicesByN(n);

	cout << "������� �������� m: ";
	cin >> m;
	array.decreaseOddElementsByM(m);

	cout << "���������� ������: ";
	array.printArray();

	cout << "��������, ������������� ������ ���� ���: ";
	array.findUniqueElements();

	return 0;
}