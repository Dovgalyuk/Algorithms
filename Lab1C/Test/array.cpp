#include "Array.h"

int main() {
	auto* array = new StaticSizeArray<int>(10);

	if (array->size() != 10) {
		std::cerr << "Invalid array size";
		return -1;
	}

	for (std::size_t index{}; index < 10; ++index) {
		array->at(index) = static_cast<int>(index) * 2;
	}

	*array = *array;

	auto copy(*array);

	for (std::size_t index{}; index < 10; ++index) {
		if (array->at(index) != index * 2
			|| copy.at(index) != index * 2) {
			std::cout << "Invalid array element: " << index << std::endl;
			return 1;
		}
	}

	delete array;
}