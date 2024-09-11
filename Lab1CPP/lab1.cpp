#include "array.h"

Data task_1(Array* array, size_t size)
{
	Data result = 0;

	array = create_random_array(size);

	for (size_t i = 1; i < array_size(array); i += 2)
	{
		if (array_get(array, i) > 0)
		{
			result += array_get(array, i);
		}
	}
	return result;
}

void task_2(Array* array, size_t size, Data a, Data b)
{
	array = create_random_array(size);

	for (size_t i = 0; i < array_size(array); i++)
	{
		if (array_get(array, i) >= a && array_get(array, i) <= b)
		{
			array_erase(array, i);
			i--;
		}
	}
}

int main()
{
	Array* arr = nullptr;
	size_t size;
	std::ifstream in("input.txt");
	if (in.is_open())
	{
		in >> size;
		task_1(arr, size);
		array_delete(arr);

		Data a, b;
		in >> size;
		in >> a;
		in >> b;
		task_2(arr, size, a, b);
		array_delete(arr);
	}
	in.close();

	return 0;
}