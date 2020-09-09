#include <iostream>
#include <cstdlib>
#include <ctime>
#include "array.h";
int main()
{
	int size;
	int max = 0;
	int arr_e;
	srand(time(0));
	std::cout << "Enter the size:";
	std::cin >> size;
	Array* arr = array_create(size);
	for (int i = 0; i < size; i++)
		array_set(arr, i, rand() % 100 - 50);
	for (int i = 0; i < size; i += 2) {
		arr_e = array_get(arr, i);
		if (arr_e > max)
			max = arr_e;
	}
	std::cout << "Max element = " << max;
	array_delete(arr);
	return 0;
}