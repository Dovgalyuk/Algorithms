#include <fstream>
#include <iostream>
#include "array.h"

Array* array_create_and_read(std::ifstream& input) {
	size_t n;
	if (!(input >> n)) {
		throw std::invalid_argument("Can't read array size");
	}

	Array* arr = array_create(n);

	for (size_t i = 0; i < n; ++i) {
		int value;
		if (!(input >> value)) {
			array_delete(arr);
			throw std::invalid_argument("Can't read value");
		}
		array_set(arr, i, value);
	}

	return arr;
}

void array_output(Array* arr) {
	for (size_t i = 0; i < array_size(arr); i++) {
		std::cout << array_get(arr, i) << " ";
	}
	std::cout << std::endl;
}


void task1(std::ifstream& input) {
	Array* arr1 = array_create_and_read(input);

	size_t count = 0;
	for (int i = 0; i < array_size(arr1); i++) {
		if (array_get(arr1, i) % 2 == 0) {
			count++;
		}
	}
	Array* arr2 = array_create(count);
	count = 0;
	size_t index_count = 0;
	while (count < array_size(arr1)) {
		if (array_get(arr1, count) % 2 == 0) {
			array_set(arr2, index_count, static_cast<Data>(count));
			index_count++;
		}
		count++;
	}

	array_output(arr1);
	array_delete(arr1);

	array_output(arr2);
	array_delete(arr2);
}

int task2(std::ifstream& input) {
	Array* arr = array_create_and_read(input);

	int maxcount = 1;
	int number = 0;
	for (size_t i = 0; i < array_size(arr); i++) {
		int count = 1;
		for (size_t j = i + 1; j < array_size(arr); j++) {
			if (array_get(arr, i) == array_get(arr, j)) {
				count++;
			}
		}
		if (maxcount < count) {
			maxcount = count;
			number = array_get(arr, i);
		}
	}
	if (maxcount < 2) std::cout << "No repeating elements or array is empty" << std::endl;
	array_output(arr);
	array_delete(arr);

	return number;
}

int main() {
	std::ifstream input("input.txt");

	if (input.is_open()) {
		task1(input);

		//input.clear();
		//input.seekg(0);

		std::cout << task2(input);
	}

	input.close();

	return 0;
}