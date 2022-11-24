#include <iostream>
#include "array.h"

using namespace std;



void FillArray(Array* arr) {
	int size = array_size(arr);
	cout << "Введите элементы массива:" << endl;
	for (int i = 0; i < size; i++) {
		int value;
		cin >> value;
		array_set(arr, i, value);
	}
}

void PrintArray(Array* arr) {
	int size = array_size(arr);
	cout << "Массив:" << endl;
	for (int i = 0; i < size; i++) {
		cout << array_get(arr, i)<<" ";
	}
	cout << endl;
}


void CheckArray(Array* arr) {
	int size = array_size(arr);

	int a = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 2; j < 10; j++)
		{
			if (array_get(arr, i) % j == 0)
			{
				a++;
				break;
			}
		}
	}
	cout << "Колво чисел кратных хотя бы одному в диапазоне от 2 до 9: " << a;
}


int main() {
	setlocale(LC_ALL, "ru");
	
	cout << "Введите размер массива: " << endl;
	int size;
	cin >> size;

	Array* massive = array_create(size);
	FillArray(massive);
	PrintArray(massive);
	CheckArray(massive);
}
