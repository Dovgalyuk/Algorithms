#include <iostream>
#include <fstream>
#include <string>
#include "array.h"

Array<int> *array_create_and_read(std::ifstream &input)
{
	size_t n;

	if (input >> n)
	{
		Array<int> *arr = new Array<int>(n);

		for (size_t i = 0; i < n; ++i)
		{
			int x;
			if (input >> x)
			{
				arr->set(i, x);
			}
		}
		return arr;
	}
	return nullptr;
}


void task2(Array<int> *arr)
{
	size_t size_arr = arr->size();

	for (size_t i = 0; i < size_arr; i++)
	{
		size_t count = 0;
		for (size_t j = 0; j < size_arr; j++)
		{
            if (i == j || arr->get(j) == 0)
			{
				count++;
				continue;
			}

            else if(arr->get(j)==arr->get(i)){
                continue;
            }

			else if (arr->get(i) % arr->get(j) == 0)
			{
				break;
			}

			count++;
		}
		if (count == size_arr)
		{
			std::cout << arr->get(i) << " ";
		}
	}
}

int main(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
	{
		return 1;
	}

	Array<int> *arr;

	std::ifstream input(argv[1]);

	arr = array_create_and_read(input);

	if (arr != nullptr)
	{
		task2(arr);
		delete arr;
	}

	input.close();
}