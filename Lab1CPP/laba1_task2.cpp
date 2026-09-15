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


void task2(const Array<int>* arr) {
	const int maximum_znach = 1000;

	int kolvo[maximum_znach + 1] = { 0 };

	size_t razmer = arr->size();
	for (size_t i = 0; i < razmer; i++) {
		int chislo = arr->get(i);
		if (chislo >= 0 && chislo <= maximum_znach) {
			kolvo[chislo]++;
		}
	}

	int samoeChastoeChislo = 0;
	int maxPovtoreniy = 0;

	for (int i = 0; i <= maximum_znach; i++) {
		if (kolvo[i] > maxPovtoreniy) {
			maxPovtoreniy = kolvo[i];
			samoeChastoeChislo = i;
		}
	}
	cout << samoeChastoeChislo << endl;
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


	Array<int>* mas2 = chtenieArray(input);

	if (mas2) {
		task2(mas2);
		delete mas2;
	}

	input.close();
	return 0;
}