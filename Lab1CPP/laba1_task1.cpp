#include "array.h"
#include <fstream>
#include <iostream>

using namespace std;

Array<int>* chtenieArray(ifstream& in) {
	int n;
	in >> n;
	if (!in) {
		return nullptr;
	}
	Array<int>* arr = new Array<int>(n);
	for (int i = 0; i < n; i++) {
		int x;
		in >> x;

		arr->set(i, x);
	}
	return arr;
}

void task1(const Array<int>* arr) {
	size_t razmer = arr->size();
	if (razmer < 3) {
		cout << "Сумма элементов массива между min и max равна " << 0 << endl;
		return;
	}

	size_t minIND = 0;
	size_t maxIND = 0;
	for (size_t i = 1; i < razmer; i++) {
		if (arr->get(i) < arr->get(minIND)) {
			minIND = i;
		}
		if (arr->get(i) > arr->get(maxIND)) {
			maxIND = i;
		}
	}

	size_t l = (minIND < maxIND) ? minIND : maxIND;
	size_t r = (minIND > maxIND) ? minIND : maxIND;

	long long sum = 0;
	for (size_t i = l + 1; i < r; i++) {
		sum += arr->get(i);
	}

	cout << sum << endl;
}


int main(int arg1, char* arg2[])
{
	setlocale(LC_ALL, "ru");

	if (arg1 != 2) {
		cerr << "Usage: " << arg2[0] << "<input_file>" << endl;
		return 1;
	}

	ifstream input(arg2[1]);
	
	if (!input.is_open()) {
		cerr << "Ошибка! Невозможно открыть файл!" << arg2[1] << endl;
	}

	Array<int>* mas1 = chtenieArray(input);
	if (mas1) {
		task1(mas1);
		delete mas1;
	}

	input.close();
	return 0;
}