#include "array.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

int Zad(Array* zar) {
	int min = 0;
	int max = 0;
	bool ser_min = false;
	bool ser_max = false;
	int sum = 0;
	int count_min = 0;
	int count_max = 0;
	for (int i = 0; i < array_size(zar); i++) {
		array_set(zar, i, rand() % 100);
		cout << array_get(zar, i) << " ";
	}
	min = array_min(zar);
	max = array_max(zar);
	for (int i = 0; i < array_size(zar); i++) {
		if (array_get(zar, i) == max) {
			ser_max = true;
			count_max++;
		}
		if (array_get(zar, i) == min) {
			ser_min = true;
			count_min++;
		}
		if (ser_max == true and ser_min == true)
			return;
		if ((ser_max == true and count_max > 1) or (ser_min == true and count_min > 1) or (array_get(zar, i) != max and array_get(zar, i) != min and (ser_max == true or ser_min == true))
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
	cout << "—умма элементов массива(без минимального и максимального элементов): " << Zad(zar) << endl;
	array_delete(zar);
}