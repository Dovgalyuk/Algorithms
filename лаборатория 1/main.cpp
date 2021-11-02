#include "array.h"
#include <iostream>
#include <cstdlib>
#include<ctime>

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	

	int size;
	std::cout << "Ââåäèòå êîëè÷åñòâî ýëåìåíòîâ: ";
	std::cin >> size;
	if (size > 0)
	{
		Array* arr = array_create(size);
		Array* arr2 = array_create(size);

		int j = -1;
		for (int i = 0; i < size; i++)
		{
			array_set(arr, i, rand());
			std::cout << "Ýëåìåíò íîìåð " << (i + 1) << ": " << array_get(arr, i) << std::endl;
			if (array_get(arr, i) % 2 == 0)
			{
				j++;
				array_set(arr2, j, array_get(arr, i));

			}
		}
		if (j > -1)
		{
			for (int i = 0; i <= j; i++)
			{
				std::cout << "Ýëåìåíò ìàññèâà 2 íîìåð " << (i + 1) << ": " << array_get(arr2, i) << std::endl;
			}
		}
		else
		{
			std::cout << "×¸òíûõ ýëèìåíòîâ â ìàññèâå íåò " << std::endl;
		}


		array_delete(arr);
		array_delete(arr2);
	}
	else
	{
		std::cout << "Íå êîðåêòíàÿ äëèííà ìàññèâà " << std::endl;
	}
	return 0;
}
