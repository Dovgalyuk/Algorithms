#include <array.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void Zad(Array* zar, Array* zar_1) 
{
	int k1 = 0;
	int k2 = 0;
	int elem = 0;
	cout << "Введите число k1: ";
	cin >> k1;
	cout << "Введите число k2: ";
	cin >> k2;
	cout << "Массив: " << endl;
	for (int i = 0; i < array_size(zar); i++) {
		array_set(zar, i, -100 + rand() % 201);
		cout << array_get(zar, i) << " ";
	}
	cout << endl;

	for (int i = 0; i < array_size(zar); i++) {
		if (array_get(zar, i) >= 0) {
			elem = array_get(zar, i) - k1;
			array_set(zar_1, i, elem);
		}
		else {
			elem = array_get(zar, i) - k2;
			array_set(zar_1, i, elem);
		}
	}
	cout << "Массив после преобразований: " << endl;
	for (int i = 0; i < array_size(zar_1); i++) {
		cout << array_get(zar_1, i) << " ";
	}
}

int main()
{
    setlocale(LC_ALL, "RUS");
    int n;
	srand((unsigned)time(NULL));
	cout << "Введите размерность массива: ";
	cin >> n;
	Array* zar = array_create(n);
	Array* zar_1 = array_create(n);
	system("cls");
	Zad(zar, zar_1);
	array_delete(zar);
    array_delete(zar_1);
	return 0;
}