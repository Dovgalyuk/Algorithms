#include <iostream>
#include <fstream>
#include <cstdlib>
#include "array.h"
using namespace std;

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru");

	if (argc < 2) {
		cout << "Не указан входной файл";
		return 1;
	}

	ifstream input(argv[1]);

	if (!input) {
		cout << "Ошибка открытия файла";
		return 1;
	}

	int n;

	if (!(input >> n)) {
		cout << "Ошибка чтения n";
		return 1;
	}

	Array arr(n);

	int value;

	for (int i = 0; i < n; i++) {
		input >> value;
		arr.set(i, value);
	}
	
	int count = 0;
	
	for (int i = 0; i < n; i++) {
		if (arr.get(i) % 2 == 0) {
			count++;
		}
	}

	if (count < 2) {
		cout << "Not enough even elements";
		return 0;
	}

	Array even(count);

	int j = 0;

	for (int i = 0; i < n; i++) {
		if (arr.get(i) % 2 == 0) {
			even.set(j, arr.get(i));
			j++;
		}
	}

	int diff;
	int min = abs(even.get(0) - even.get(1));
	for (int i = 0; i < count; i++) {
		for (int k = i + 1; k < count; k++) {
			diff = abs(even.get(i) - even.get(k));

			if (diff < min) {
				min = diff;
			}
		}
	}
	cout << min;


	return 0;
}