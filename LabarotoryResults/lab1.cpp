#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "array.h"


int main() {
	
	int size, min;
	min = 10000;
	srand(time(NULL));
	std::cout << "Massive size = ";
	std::cin >> size;
	Array* arr = array_create(size);
	for (int i = 0; i < size; ++i){
		array_set(arr, i, 1 + rand() % 999);
	}

	for (int i = 0; i < size; i++)
	{
		if (array_get(arr, i) % 2 == 0)
		{
			for (int j = (i + 1); j < size; j++) 
			{
				if ((array_get(arr, j) % 2 == 0) && 
					(min >= abs(array_get(arr, i) - array_get(arr, j))) && 
					(array_get(arr, i) != array_get(arr, j)))
				{
					min = abs(array_get(arr, i) - array_get(arr, j));
				}
			}
		}
		std::cout << array_get(arr, i) << std::endl;
	}
	if (min == 10000) std::cout << "Error" << std::endl;
	else std::cout << "Min " << min << std::endl;
	return 0;
}