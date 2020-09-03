#include <iostream>
#include <ctime>

#include "array.h"

void print(Array* arr, size_t size)
{	
	for(int i = 0; i < size; i++)
	{
		std::cout << array_get(arr, i) << " "; 
	}
	std::cout << std::endl;
}

void arrayCompressor(Array* arr, int a, int b, size_t arrSize)
{
	Array* newArray = array_create(arrSize);
	size_t extraNumbers = 0;

	for (int i = 0; i < arrSize; i++)
	{
		if (array_get(arr, i) >= a && array_get(arr, i) <= b)
		{
			extraNumbers++;
			array_set(newArray, arrSize - extraNumbers, 0);
			continue;
		}
		array_set(newArray, i - extraNumbers, array_get(arr, i));
	}

	for(int i = 0; i < arrSize; i++)
		array_set(arr, i, array_get(newArray, i));

	array_delete(newArray);
}

int main()
{
	size_t arrSize;
	int a, b;

	srand(time(0));

	std::cout << "Enter the size of the array: ";
	std::cin >> arrSize;

	std::cout << "Enter a and b values: ";
	std::cin >> a >> b;
	
	Array *arr = array_create(arrSize);
	
	for (int i = 0; i < arrSize; i++)
		array_set(arr, i, rand() % 100 - 50);

	print(arr, arrSize);
	arrayCompressor(arr, a, b, arrSize);
	print(arr, arrSize);

	array_delete(arr);

	return 0;
}
