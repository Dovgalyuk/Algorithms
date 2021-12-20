#include "array.cpp"
#include <iostream>
#include <ctime>
#include <stdlib.h>
int main()
{
	int size;
	std::cout << "Enter the dimension of the array: ";
	std::cin >> size;

	Array* arr = array_create(size);

	std::srand(std::time(nullptr));
	for (int i = 0; i < array_size(arr); i++) 
	{
		array_set(arr, i, rand() % 100);
	}

	int min = 0, max = 0;
	for (int i = 0; i < array_size(arr); i++)
	{
		if (min >= array_get(arr, i)) min = array_get(arr, i);
		if (max <= array_get(arr, i)) max = array_get(arr, i);
	}

	int count = 0;
	for (int i = 0; i < array_size(arr); i++)
	{
		if ((array_get(arr, i)) > ((min + max)/2))
		{
			std::cout << i << " ";
			count++;
		}
	}
	std::cout << "Number of elements: " << count << std::endl;
	return 0;
}