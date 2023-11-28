#include <iostream>

using namespace std;
#include <ctime>

#include "array.h"

void print_data(Array* arr) {
	for (int i = 0; i < array_size(arr); i++) {
		cout << array_get(arr, i) << " ";
	}
	cout << endl;
}

Array* random_full() {
	size_t size;
	cin >> size;
	Array* newArray = NULL;
	newArray = array_create(size);
	for (int i = 0; i < size; i++) {
		array_set(newArray, i, 1 + rand() % 10);
	}

	return newArray;
}

void bubble_sort(int* arr, int n) {
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
		}
}

Array* delete_elements() {
	Array* newArray = NULL;
	newArray = random_full();

	print_data(newArray);

	int n;
	int m;
	cin >> n;
	cin >> m;

	//bubble_sort(newArray->data, newArray->size);  // сортировка не нужна!!!

	for (int i = 0; i < array_size(newArray); i++) {
		if (array_get(newArray, i) >= n && array_get(newArray, i) <= m) {
			array_set(newArray, i, 0);
		}
	}

	return newArray;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	//РАСКОМЕНТИРОВАТЬ

	cout << "Рандомный массив" << endl;
	Array* a = NULL;
	a = random_full();
	print_data(a);

	cout << "Введите количество элементов массива, затем выберите интервал двумя числами" << endl;
	Array* b = NULL;
	b = delete_elements();
	print_data(b);

	cout << "Введите количество элементов массива, выводит сумму четных" << endl;
	Array* c = NULL;
	//sum_elements();
	print_data(c);

	return 0;
}