#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <array>
using namespace std;
void first_podschet(const vector<int>& arr, int N) {
	cout << "Массив: ";
	for (int k = 0; k < N; k++) {
		cout << arr[k] << " ";
	}
	cout << endl;
	int minus = 0, plus = 0, nol = 0;
	for (int j = 0; j < N; j++) {
		if (arr[j] < 0) {
			minus += 1;
		}
		if (arr[j] > 0) {
			plus += 1;
		}
		if (arr[j] == 0) {
			nol += 1;
		}
	}
	cout << "Положительных чисел: " << plus << endl;
	cout << "Отрицательных чисел: " << minus << endl;
	cout << "Нулевых чисел: " << nol << endl;

}
void second_deleters(const vector<int>& arr, int N) {
	cout << "Массив: ";
	for (int k = 0; k < N; k++) {
		cout << arr[k] << " ";
	}
	cout << endl;
	for (int i = 0; i < N; i++) {
		bool notDelete = true;
		for (int j = 0; j < N; j++) {
			if ((i != j) && (arr[i] % arr[j] == 0)) {
				notDelete = false;
				break;
			}
		}
		if (notDelete) {
			cout << "Не делющиеся число: " << arr[i] << endl;
		}
		cout << endl;
	}

}
int main()
{
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
			array<int, 6 > arr = { 5, 7, 1, 2, 4, 9 };
			cout << "Контейнер Array: ";
			for (int i = 0; i < (int)arr.size(); i++) {
				cout << arr[i] << " ";
			}
			cout << endl;
		}
		if (choise == 2) {
			int N;
			cout << "Введите размер массива: ";
			cin >> N;
			vector<int> mas(N);
			srand(time(0));
			for (int i = 0; i < N; i++) {
				mas[i] = rand() % 201 - 100;
			}
			cout << endl;
			first_podschet(mas, N);
		}
		if (choise == 3) {
			int N;
			cout << "Введите размер массива: ";
			cin >> N;
			vector<int> mas(N);
			srand(time(0));
			for (int i = 0; i < N; i++) {
				mas[i] = rand() % 201 - 100;
			}
			cout << endl;
			second_deleters(mas, N);
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
