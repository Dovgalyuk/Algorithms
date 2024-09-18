#include "array.h"
#include <fstream>
#include <iostream>


Array* array_create_and_read(std::ifstream& input) {
	size_t n;
	if (!(input >> n)) {
		throw std::invalid_argument("Failed");
	}
	Array* arr = array_create(n);
	for (size_t i = 0; i < n; ++i) {
		int x;
		if (!(input >> x)) {
			throw std::invalid_argument("Failed");
		}
		array_set(arr, i, x);
	}
	return arr;

}

void task1(std::ifstream& input)
{
	Array* arr = array_create_and_read(input);
	int sum = 0;
	for (size_t i = 0; i < array_size(arr); ++i) {
		int val = array_get(arr, i);
		if (val > 20) sum += val;
	}
	std::cout << "Does the sum of the elements (>20) exceed 100?:\n";
	if (sum == 0) {
		std::cout << "There is no such elements in array\n";
	}
	else if (sum > 100) {
		std::cout << "Yes\n";
	}
	else std::cout << "No\n";

	sum = 0;
    int count = 0;
	for (size_t i = 0; i < array_size(arr); ++i) {
		int val = array_get(arr, i);
		if (val < 50){
            sum += val;
            count++;
        }
	}
	std::cout << "Is the sum of the elements (<50) a multiple of 2?:\n";
	if (count == 0) {
		std::cout << "There is no such elements in array\n";
	}
	else if (sum % 2 == 0) {
		std::cout << "Yes\n";
	}
	else std::cout << "No\n";

	array_delete(arr);

}


void task2(std::ifstream& input) {
	Array* arr = array_create_and_read(input);
	int a;
	int b;
	if (!(input >> a)) {
		throw std::invalid_argument("Failed");
	}
	if (!(input >> b)) {
		throw std::invalid_argument("Failed");
	}

	size_t ind = 0;

	for (size_t i = 0; i < array_size(arr); i++) {
		if (array_get(arr, i) < a || array_get(arr, i) > b) {
			array_set(arr, ind++, array_get(arr, i));
		}
	}

	while (ind < array_size(arr)) {
		array_set(arr, ind++, 0);
	}

	std::cout << "Compressed array:\n";
	for (size_t i = 0; i < array_size(arr); ++i) {
		std::cout << array_get(arr, i) << " ";
	}
	std::cout << std::endl;

	array_delete(arr);
}


int main() {
	std::ifstream input("input.txt");
	if (input.is_open()) {
	task1(input);
	task2(input);
    }
	input.close();

}