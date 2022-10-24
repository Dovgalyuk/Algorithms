#include "array.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

int Zad(Array* zar, int const SIZE) {
	int sum = 0;
	count = 0;
	for (int i = 0; i < SIZE; i++) {
		array_set(zar, i, rand() % 100);
		cout << array_get(zar, i) << " ";
	}
	for (int i = 0; i < SIZE; i++) {
		if (array_get(zar, i) == array_min(zar) or array_get(zar, i) == array_max(zar))
			count++;
		if (count == 1 and array_get(zar, i) != array_min(zar) and array_get(zar, i) != array_max(zar))
			sum += array_get(zar, i);
	}
	return sum;
}

int main(){
	srand(time(NULL));
	setlocale(LC_ALL, "RUS");
	int n;
	cout << "¬ведите размерность массива: ";
	cin >> n;
	Array* zar = array_create(n);
	cout << "—умма элементов массива(без минимального и максимального элементов): " << Zad(zar, n) << endl;
	array_delete(zar);
}