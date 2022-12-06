#include <iostream>
#include"array.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	bool check;
	int size = 0, divider, dividend;
	Array* A = NULL;

	cout << "Введите размер массива: ";
	cin >> size;

	A = array_create(size);

	for (int i = 0; i < size; i++) array_set(A, i, rand() % 100 + 1);

	cout << "\nВаш массив: ";

	for (int i = 0; i < size; i++) cout << array_get(A, i) << ' ';

	cout << endl << endl;

	for (size_t i = 0; i < size; i++) {
		check = true;
		for (size_t j = 0; j < size; j++) {
			dividend = array_get(A, i);
			divider = array_get(A, j);
			if (dividend % divider == 0 && i != j && dividend != divider) {
				check = false;
				break;
			}
		}
		if (check) cout << dividend << " не делится ни на один из элементов\n";
		else cout << dividend << " делится на " << divider << "\n";
	}

	return 0;
}
