#include "../LibraryCPP/array.h"
#include <iostream>

int main()
{
	int size, x;
	std::cout << "Enter the size of the array:" << std::endl;
	std::cin >> size;
	Array* ptrarr = array_create(size);
	for (int i = 0; i < size; i++)
		array_set(ptrarr, i, rand());

	std::cout << std::endl << "Array in direct order:" << std::endl;
	for (int i = 0; i < size; i++)
		std::cout << array_get(ptrarr, i) << " | ";
	std::cout << std::endl;
	std::cout << "==" << std::endl << "====" << std::endl << "========"
		<< std::endl << "====" << std::endl << "==" << std::endl;

	for (int i = 0, size2 = size - 1; i < size / 2; i++, size2--)
	{
		x = array_get(ptrarr, size2);
		array_set(ptrarr, size2, array_get(ptrarr, i));
		array_set(ptrarr, i, x);
	}

	std::cout << "Array in reverse order:" << std::endl;
	for (int i = 0; i < size; i++)
		std::cout << array_get(ptrarr, i) << " | ";
	std::cout << std::endl;
	array_delete(ptrarr);
}