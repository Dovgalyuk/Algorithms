#include "../LibraryCPP/array.h"
#include <iostream>
#include <cstdlib>

int main() 
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	int count1 = 0;
	int count2 = 0;
	
	int size;
	std::cout << "Введите количество элементов: ";
	std::cin >> size;

	Array* arr = array_create(size);

	for (int i = 0; i < size; i++)
	{
		array_set(arr, i, rand());
		
		if (array_get(arr, i) % 2 == 0)
			count1 += 1;
		else if (array_get(arr, i) % 10 == 5)
			count2 += 1;

		std::cout << "Элемент номер " << (i + 1) << ": " << array_get(arr, i) << std::endl;
	}

	std::cout << std::endl << "Количество чётных чисел: " << count1 << std::endl;
	std::cout << "Количество чисел с цифрой 5 на конце: " << count2 << std::endl;

	return 0;
}