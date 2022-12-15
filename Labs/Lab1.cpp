#include <iostream>
#include "array.h"
#include <ctime>

void FillingArray(Array* arr) {
	srand(time(NULL));
	for (int index = 0; index < array_size(arr); index++) {
		array_set(arr, index, rand() % 201 - 100);
	}
}

int Sum(Array* arr) {
	int res = 0;
	for (int i = 0; i < array_size(arr); i++)
	{
		std::cout << array_get(arr, i) << '\n';
	}
	for (int i = 0; i < array_size(arr); i++) {
		if (array_get(arr, i) <= 20) {
			res += array_get(arr, i);
		}
	}
	return res;
}

int main() {

	int size;
	std::cout << "Size: ";
	std::cin >> size;

	Array* array = array_create(size);
	FillingArray(array);
	std::cout << "Sum: " << Sum(array) << '\n';
	array_delete(array);
}