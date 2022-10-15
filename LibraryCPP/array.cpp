#include "array.h"
#include <stdlib.h>
#include <iostream>
using namespace std;
typedef int Data;
typedef Array<Data> MyArray;

int main(){
	srand(time(NULL));
	setlocale(LC_ALL, "RUS");
	int n;
	int sum = 0;
	cout << "Введите размерность массива: ";
	cin >> n;
	MyArray* array = new MyArray(n);
	for (int i = 0; i < n; i++) {
		array->set(i, rand() % 100);
	}
	cout << "Массив: ";
	array->output();
	cout << endl;
	array->sort();
	cout << "Массив(отсортированный): ";
	array->output();
	cout << endl;
	for (int i = 0; i < array->size(); i++) {
		if (array->get(i) != array->max() and array->get(i) != array->min()) {
			sum += array->get(i);
		}
	}
	cout << "Сумма элементов массива(без минимального и максимального элементов): " << sum << endl;
}