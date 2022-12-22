#include <iostream>
#include <ctime>
#include "array.h"

using namespace std;

void FillingArray(Array* arr) {
	srand(time(NULL));
	for (int index = 0; index < array_size(arr); index++) {
		array_set(arr, index, rand() % 201 +(-100));
		cout << array_get(arr, index) << "  ";
	}
}

void ÑountingÑhanges(const Array* arr) {
	int NumberOfChanges = 0;
	for (int index = 0; index < array_size(arr); index++) {
		NumberOfChanges += ((array_get(arr, index) * (array_get(arr, index + 1))) < 0);
	}
	cout << "\ncount of changes: " << NumberOfChanges << '\n';
}

int main() {
	int ArraySize;
	cout << "enter the number of items: ";
	cin >> ArraySize;
	cout << "array of " << ArraySize << " elements:\n";

	Array* DataArray = array_create(ArraySize);
	FillingArray(DataArray);
	ÑountingÑhanges(DataArray);
	array_delete(DataArray);

	return 0;
}

