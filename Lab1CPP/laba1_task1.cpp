#include "array.h"
#include <fstream>
#include <iostream>

using namespace std;

Array* chtenieArray(ifstream& in) {
	int n;
	in >> n;
	if (!in) {
		return nullptr;
	}
	Array* arr = array_create(n);
	for (int i = 0; i < n; i++) {
		int x;
		in >> x;

		array_set(arr, i, x);
	}
	return arr;
}

void task1(const Array* arr) {
	size_t razmer = array_size(arr);
	if (razmer < 3) {
		cout << 0 << endl;
		return;
	}

	size_t minIND = 0;
	size_t maxIND = 0;
	for (size_t i = 1; i < razmer; i++) {
		if (array_get(arr, i) < array_get(arr, minIND)) {
			minIND = i;
		}
		if (array_get(arr, i) > array_get(arr, maxIND)) {
			maxIND = i;
		}
	}

	size_t l = (minIND < maxIND) ? minIND : maxIND;
	size_t r = (minIND > maxIND) ? minIND : maxIND;

	long long sum = 0;
	for (size_t i = l + 1; i < r; i++) {
		sum += array_get(arr, i);
	}

	cout << sum << endl;
}


int main(int arg1, char* arg2[])
{
	setlocale(LC_ALL, "ru");

	if (arg1 != 2) {
		cerr << "Usage: " << arg2[0] << " <input_file>" << endl;
		return 1;
	}

	ifstream input(arg2[1]);

	if (!input.is_open()) {
		cerr << "Ошибка! Невозможно открыть файл!" << arg2[1] << endl;
		return 1;
	}

	Array* mas1 = chtenieArray(input);
	if (mas1) {
		task1(mas1);
		array_delete(mas1);
	}

	input.close();
	return 0;
}