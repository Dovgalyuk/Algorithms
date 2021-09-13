#include <iostream>

int main()
{
	int size, x;
	std::cout << "Enter the size of the array:" << std::endl;
	std::cin >> size;
	int* ptrarr = new int[size];
	for (int i = 0; i < size; i++)
		ptrarr[i] = rand();

	std::cout << std::endl << "Array in direct order:" << std::endl;
	for (int i = 0; i < size; i++)
		std::cout << ptrarr[i] << " | ";
	std::cout << std::endl;
	std::cout << "==" << std::endl << "====" << std::endl << "========"
		<< std::endl << "====" << std::endl << "==" << std::endl;

	for (int i = 0, size2 = size - 1; i < size / 2; i++, size2--)
	{
		x = ptrarr[size2];
		ptrarr[size2] = ptrarr[i];
		ptrarr[i] = x;
	}

	std::cout << "Array in reverse order:" << std::endl;
	for (int i = 0; i < size; i++)
		std::cout << ptrarr[i] << " | ";
	std::cout << std::endl;
	delete[] ptrarr;
}