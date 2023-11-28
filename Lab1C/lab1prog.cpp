#include <iostream>
#include <cstdlib>
#include <ctime>
#include "C:\\Users\Мирослав\Desktop\Algorithms\LibraryCPP\array.h" 
#include "C:\\Users\Мирослав\Desktop\Algorithms\LibraryCPP\array.cpp" 
using namespace std;

void first_podschet(const Array& arr) {
	cout << "Массив: ";
	for (size_t k = 0; k < array_size(&arr); k++) {
		cout << array_get(&arr, k) << " ";
	}
	cout << endl;

	int minus = 0, plus = 0, nol = 0;
	for (size_t j = 0; j < array_size(&arr); j++) {
		if (array_get(&arr, j) < 0) {
			minus += 1;
		}
		if (array_get(&arr, j) > 0) {
			plus += 1;
		}
		if (array_get(&arr, j) == 0) {
			nol += 1;
		}
	}
	cout << "Положительных чисел: " << plus << endl;
	cout << "Отрицательных чисел: " << minus << endl;
	cout << "Нулевых чисел: " << nol << endl;
}

void second_deleters(const Array& arr) {
	cout << "Массив: ";
	for (size_t k = 0; k < array_size(&arr); k++) {
		cout << array_get(&arr, k) << " ";
	}
	cout << endl;

	for (size_t i = 0; i < array_size(&arr); i++) {
		bool notDelete = true;
		for (size_t j = 0; j < array_size(&arr); j++) {
			if ((i != j) && (array_get(&arr, i) % array_get(&arr, j) == 0)) {
				notDelete = false;
				break;
			}
		}
		if (notDelete) {
			cout << "Не делющиеся число: " << array_get(&arr, i) << endl;
		}
	}
}

int main() {
	setlocale(LC_ALL, "rus");

	cout << endl;
	bool oneMoreTime = true;
	while (oneMoreTime) {
		int choise;
		cout << "Выберите задание(0 - Выход)" << endl;
		cout << "1-Контейнер Array" << endl;
		cout << "2-Подсчет положительных,отрицательных,нулевых" << endl;
		cout << "3-Не делющиеся элементы" << endl;
		cin >> choise;

		if (choise == 1) {
			const size_t n = 6;
			Array* arr = array_create(n);
			array_set(arr, 0, 5);
			array_set(arr, 1, 7);
			array_set(arr, 2, 1);
			array_set(arr, 3, 2);
			array_set(arr, 4, 4);
			array_set(arr, 5, 9);

			cout << "Контейнер Array: ";
			for (size_t i = 0; i < array_size(arr); i++) {
				cout << array_get(arr, i) << " ";
			}
			cout << endl;

			array_delete(arr);
		}

		if (choise == 2) {
			const size_t N = 6;
			Array* arr = array_create(N);

			srand(time(0));
			for (size_t i = 0; i < array_size(arr); i++) {
				array_set(arr, i, rand() % 201 - 100);
			}

			cout << endl;
			first_podschet(*arr);
			array_delete(arr);
		}

		if (choise == 3) {
			const size_t N = 6;
			Array* arr = array_create(N);

			srand(time(0));
			for (size_t i = 0; i < array_size(arr); i++) {
				array_set(arr, i, rand() % 201 - 100);
			}

			cout << endl;
			second_deleters(*arr);
			array_delete(arr);
		}

		if (choise == 0) {
			oneMoreTime = false;
		}

		if (choise != 0) {
			int oneMoreTimeOrNot;
			cout << "Запустить программу снова? (1 - Да, 0 - Нет): ";
			cin >> oneMoreTimeOrNot;
			cout << endl;

			if (oneMoreTimeOrNot == 1) {
				continue;
			}
			else {
				oneMoreTime = false;
			}
		}
	}

	return 0;
}