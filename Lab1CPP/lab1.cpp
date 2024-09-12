#include "array.h"	
#include <iostream>

Data task_1(Array*& array, std::ifstream& in)
{
	Data result = 0;

	array = fill_array(in);

	for (size_t i = 0; i < array_size(array); i++)
	{
		if (array_get(array, i) > 0 && array_get(array, i) % 2 == 0)
		{
			result += array_get(array, i);
		}
	}
	return result;
}

void task_2(Array*& array, std::ifstream& in)
{
	array = fill_array(in);

	Data a, b;
	in >> a >> b;

	size_t k = 0;
	for (size_t i = 0; i < array_size(array); i++)
	{
		if (!(array_get(array, i) >= a && array_get(array, i) <= b))
		{
			if (i != k) 
				array_set(array, k, array_get(array, i));
			++k;
		}
	}

	for (size_t i = k; i < array_size(array); i++)
		array_set(array, i, 0);
}

int main()
{
	std::ifstream in("input.txt");
	if (in.is_open())
	{
		Array* arr = NULL;

		if (task_1(arr, in) != 30)
			std::cout << "task_1 error result!" << std::endl;
		array_delete(arr);

		task_2(arr, in);
		array_delete(arr);
	}
	in.close();

	return 0;
}
