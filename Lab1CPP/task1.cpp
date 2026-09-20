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

	int signChanges = 0;
	for (size_t i = 1; i < n; ++i) {
		int prev = arr.get(i - 1);
		int curr = arr.get(i);
		if ((prev > 0 && curr < 0) || (prev < 0 && curr > 0)) {
			++signChanges;
		}
	}

	std::cout << signChanges << std::endl;
	return 0;
}