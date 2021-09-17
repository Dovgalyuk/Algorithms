#include <iostream>
#include <cstdlib>
#include <ctime>
#include "array.h"

using namespace std;

int GiveMeSize() {
	int size, check;
	do {
		cout << "Give me size of the massive: ";
		cin >> size;
		if (cin.fail())
		{
			check = 0;
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "\nOh-oh, looks like you made a mistake. Here is your next chanse\n";
		}
		else {
			check = 1;
		}
	} while (check == 0);
	cout << "\n";
	return size;
}

void FillingArray(Array* array, int* arrayCopy) {
	srand(time(nullptr));
	cout << "We got this:\n";
	for (int i = 0; i < array_size(array); i++) {
		arrayCopy[i] = rand() % 41 - 20;
		//arrayCopy is here to make the result more beautiful, because i can
		array_set(array, i, arrayCopy[i]);
		cout << i + 1 << " element: " << array_get(array, i) << "\n";
	}
	cout << "\n";
}

void subtractionk1k2(Array* array) {
	int k1, k2;
	cout << "enter k1: ";
	cin >> k1;
	cout << "\nenter k2: ";
	cin >> k2;
	for (int i = 0; i < array_size(array); i++) {
		if (array_get(array, i) > 0) {
			array_set(array, i, array_get(array, i) - k1);
		}
		if (array_get(array, i) <= 0) {
			array_set(array, i, array_get(array, i) - k2);
		}
	}
	cout << "\n\n";
}

void Result(Array* array, int* arrayCopy) {
	cout << "It was:\r\t\t\tIt became:\n";
	for (int i = 0; i < array_size(array); i++) {
		cout << i + 1 << " element: " << arrayCopy[i] << "\r\t\t\t" << i + 1 << " element: " << array_get(array, i) << "\n";
	}
}

int main()
{
	int size = GiveMeSize();
	Array* array = array_create(size);
	int *arrayCopy = new int[size];
	FillingArray(array, arrayCopy);
	subtractionk1k2(array);
	Result(array, arrayCopy);
	array_delete(array);
	delete[] arrayCopy;
	arrayCopy = 0;
	return 0;
}
