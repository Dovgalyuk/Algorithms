#include <iostream>
#include <fstream>
#include "array.h"
using namespace std;

Array* ArrayCreateAndRead(ifstream& input, int& a, int& b, int& ln) {
	int n;
	input >> n;
	ln++;
	Array* arr = array_create(n);
	for (int i = 0; i < n; i++) {
		int x;
		input >> x;
		array_set(arr, i, x);
	}
	ln++;
	if (ln == 5) {
		input >> a >> b;
	}
	return arr;
}

void Task1(Array* arr) {
	size_t size = array_size(arr);
	int element;
	int month_1half_summ = 0, month_2half_summ = 0;
	int month_1decade = 0, month_2decade = 0, month_3decade = 0;
	for (size_t i = 0; i < size; i++) {
		element = array_get(arr, i);
		if (i < size / 2) {
			month_1half_summ += element;
			if (i < 10) {
				month_1decade += element;
			}
			else {
				month_2decade += element;
			}
		}
		else {
			month_2half_summ += element;
			if (i < 20) {
				month_2decade += element;
			}
			else {
				month_3decade += element;
			}
		}
	}
	if (month_1half_summ > month_2half_summ) {
		printf("В первую половину июня выпало больше осадков (%d мм).\n", month_1half_summ);
	}
	else {
		printf("Во вторую половину июня выпало больше осадков (%d мм).\n", month_2half_summ);
	}
	if ((month_1decade > month_2decade) && (month_1decade > month_3decade)) {
		printf("Больше всего осадков выпало в первую декаду месяца (%d мм).\n", month_1decade);
	}
	else if ((month_2decade > month_1decade) && (month_2decade > month_3decade)) {
		printf("Больше всего осадков выпало во вторую декаду месяца (%d мм).\n", month_2decade);
	}
	else {
		printf("Больше всего осадков выпало в третью декаду месяца (%d мм).\n", month_3decade);
	}
}

void Task2(Array* arr, int a, int b) {
	size_t size = array_size(arr);
	int element;
	int cnt = 0;
	for (size_t i = 0; i < size; i++) {
		element = array_get(arr, i);
		if (element < a || element > b) {
			array_set(arr, i - cnt, element);
		}
		else {
			cnt++;
		}
	}
	for (size_t i = size - cnt; i < size; i++) {
		array_set(arr, i, 0);
	}
	cout << "Массив после сжатия: ";
	for (size_t i = 0; i < size; i++) {
		cout << array_get(arr, i) << " ";
	}
}

int main(int argc, char** argv) {
	if (argc != 2) {
		return 1;
	}
	setlocale(LC_ALL, "RUS");
	int a, b;
	int line_number = 1;
	ifstream input(argv[1]);
	if (!(input.is_open())) {
		cout << "Не удалось открыть файл.";
		return 1;
	}
	cout << "Task 1" << endl;
	Array* arr1 = ArrayCreateAndRead(input, a, b, line_number);
	Task1(arr1);
	array_delete(arr1);
	cout << "Task 2" << endl;
	Array* arr2 = ArrayCreateAndRead(input, a, b, line_number);
	Task2(arr2, a, b);
	array_delete(arr2);
	input.close();
	return 0;
}