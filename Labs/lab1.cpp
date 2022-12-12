#include <iostream>
#include "array.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	cout << "input size: ";
	int size;
	cin >> size;

	Array* first_arr = array_create(size);
	Array* second_arr = array_create(size);

	for (size_t i = 0; i < size; i++) { array_set(first_arr, i, rand() % 100); }

	cout << "first array: ";
	for (size_t i = 0; i < size; i++) { cout << array_get(first_arr, i) << " "; }

	for (size_t i = 0; i < size; i++) array_set(second_arr, size - i - 1, array_get(first_arr, i));

	cout << "\nsecond array: ";

	for (size_t i = 0; i < size; i++) { cout << array_get(second_arr, i) << " "; }

	cout << "\n\n";

	return 0;
}