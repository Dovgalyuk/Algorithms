#include <fstream>
#include <iostream>
#include "array.h"
using namespace std;

int main(int argc, char **argv) {
	if (argc < 2) {
		return 1;
	}

	ifstream input(argv[1]);
	if (!input) {
		return 1;
	}

	size_t size = 0;
	input >> size;

	Array<int> numbers(size);

	for (size_t i = 0; i < size; i++) {
		int value = 0;
		input >> value;
		numbers.set(i, value);
	}

	size_t min_index = 0;
	size_t max_index = 0;


	for (size_t i = 1; i < size; i++) {
		if (numbers.get(i) < numbers.get(min_index)) {
			min_index = i;
		}
		if (numbers.get(i) > numbers.get(max_index)) {
			max_index = i;
		}
	}


	size_t left = min_index;
	size_t right = max_index;

	if (left > right) {
		size_t tp = left;
		left = right;
		right = tp;
	}

	int sum = 0;
	for (size_t i = left + 1; i < right; i++) {
		sum += numbers.get(i);
	}
	cout << sum << "\n";
}