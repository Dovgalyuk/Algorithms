#include <iostream>
#include "vector.hpp"

using namespace std;

int main()
{
	Vector<int> test;

	test.resize(5);

	if (test.size() != 5)
		std::cout << "Invalid resize\n";

	for (size_t i = 0; i < test.size(); ++i)
		test.set(i, i);

	for (size_t i = 0; i < test.size(); ++i)
		if (test.get(i) != i)
			std::cout << "Invalid vector element " << i << "\n";

	test.resize(10);

	if (test.size() != 10)
		std::cout << "Invalid resize\n";

	std::cout << "Vector: ";
	for (size_t i = 0; i < test.size(); ++i)
		std::cout << test.get(i) << " ";
	std::cout << "\n";

	test.resize(3);

	if (test.size() != 3)
		std::cout << "Invalid resize\n";

	for (size_t i = 0; i < test.size(); ++i)
		if (test.get(i) != i)
			std::cout << "Invalid vector element " << i << "\n";

	std::cout << "Vector: ";
	for (size_t i = 0; i < test.size(); ++i)
		std::cout << test.get(i) << " ";
	std::cout << "\n";

	// Performance test
	for (int i = 0; i < 10000000; ++i)
		test.resize(i);
}