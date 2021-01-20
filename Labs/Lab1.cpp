#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <limits>
#include "array.h"
using namespace std;

int main()
{
	size_t arr_size;
	cout << "Enter array size: ";
	cin >> arr_size;

	Array* arr = array_create(arr_size);

	srand(time(0));

	for (int i = 0; i < arr_size; i++)
	{
		array_set(arr, i, rand());
	}

	size_t min_diff = LLONG_MAX;
	for (int i = 0; i < arr_size; i++)
	{
		int i_elem = array_get(arr, i);
		if (i_elem % 2 == 0)
		{
			for (int j = i + 1; j < arr_size; j++) 
			{
				int j_elem = array_get(arr, j);
				if (j_elem % 2 == 0)
				{
					size_t diff = abs(abs(i_elem) - abs(j_elem));
					if (diff < min_diff)
					{
						min_diff = diff;
					}
				}
			}
		}
	}

	if (min_diff != LLONG_MAX) cout << "Minimal difference between two even elements is: " << min_diff; 
}