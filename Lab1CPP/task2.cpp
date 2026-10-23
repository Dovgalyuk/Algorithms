#include "array.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
		return 1;
	}

	std::ifstream infile(argv[1]);
	if (!infile.is_open()) {
		std::cerr << "Cannot open file" << argv[1] << std::endl;
		return 1;
	}

	size_t n;
	if (!(infile >> n)) {
		std::cerr << "Invalid input file" << std::endl;
		return 1;
	}

	Array arr(n);
	for (size_t i = 0; i < n; ++i) {
		int x;
		infile >> x;
		arr.set(i, x);
	}

	size_t count = 0;
	for (size_t i = 0; i < n; ++i) {
		bool isDivisible = false;
		for (size_t j = 0; j < n; ++j) {
			if (i == j) continue;
			int other = arr.get(j);
			if (other != 0 && arr.get(i) % other == 0) {
				isDivisible = true;
				break;
			}
		}
		if (!isDivisible)  ++count;
	}

	Array result(count);

	size_t idx = 0;
	for (size_t i = 0; i < n; ++i) {
		bool isDivisible = false;
		for (size_t j = 0; j < n; ++j) {
			if (i == j) continue;
			int other = arr.get(j);
			if (other != 0 && arr.get(i) % other == 0) {
				isDivisible = true;
				break;
			}
		}
		if (!isDivisible) {
			result.set(idx++, arr.get(i));
		}
	}

	for (size_t i = 0; i < result.size(); ++i) {
		std::cout << result.get(i) << (i + 1 == result.size() ? "" : " ");
	}
	std::cout << std::endl;
	return 0;
}