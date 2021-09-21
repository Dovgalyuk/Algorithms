#include <iostream>
#include <cstdlib>
#include <ctime>
#include "array.h"

using namespace std;

int GiveMeSize() {
	int size;
	bool check;
	do {
		cout << "Give me size of the massive: ";
		cin >> size;
		if (cin.fail())
		{
			check = false;
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "\nOh-oh, looks like you made a mistake. Here is your next chanse\n";
		}
		else {
			check = true;
		}
	} while (check == false);
	cout << "\n";
	return size;
}

void FillingArray(Array* array) {
	srand(time(nullptr));
	cout << "We got this:\n";
	for (int i = 0; i < array_size(array); i++) {
		array_set(array, i, rand() % 41 - 20);
		cout << i + 1 << " element: " << array_get(array, i) << "\n";
	}
	cout << "\n";
}

void subtractionk1k2(Array* array) {
	int k1, k2;
	bool check;
	do {
		cout << "enter k1: ";
		cin >> k1;
		if (k1 < 0 || k1 > array_size(array))
		{
			check = false;
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "\nOh-oh, looks like you made a mistake. Here is your next chanse\n";
		}
		else {
			check = true;
		}
	} while (check == false);
	do {
		cout << "\nenter k2: ";
		cin >> k2;
		if (k2 < 0 || k2 > array_size(array))
		{
			check = false;
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "\nOh-oh, looks like you made a mistake. Here is your next chanse\n";
		}
		else {
			check = true;
		}
	} while (check == false);
	k1 = array_get(array, k1 - 1);
	k2 = array_get(array, k2 - 1);
	for (int i = 0; i < array_size(array); i++) {
		if (array_get(array, i) > 0) {
			array_set(array, i, array_get(array, i) - k1);
			cout << "+\n";
		}
		else if (array_get(array, i) <= 0) {
			array_set(array, i, array_get(array, i) - k2);
			cout << "-\n";
		}
	}
	cout << "\n\n";
}

void Result(Array* array) {
	cout << "It became:\n";
	for (int i = 0; i < array_size(array); i++) {
		cout << i + 1 << " element: " << array_get(array, i) << "\n";
	}
}

int main()
{
	int size = GiveMeSize();
	Array* array = array_create(size);
	FillingArray(array);
	subtractionk1k2(array);
	Result(array);
	array_delete(array);
	return 0;
}
