#include <iostream>
#include "array.h"

struct Array
{
	Data* _arr;
	size_t _n;

	Array(size_t n)
	{
		_n = n;
		_arr = new Data[_n];
	}

	// ~Array()
	// {
	//	delete[] _arr;
	// }
};

// returns array size
size_t array_size(const Array arr)
{
	//return 0;
	return arr._n;
}

// create array
Array *array_create(size_t size)
{
	return new Array(size);
}

// delete array, free memory
// returns specified array element
Data array_get(const Array arr, size_t index)
{// return (Data)0;
	if (index >= array_size(arr))
		return 0;
	else
		return arr._arr[index];
}

// sets the specified array element to the value
void array_set(Array arr, size_t index, Data value)
{
	if (index >= array_size(arr))
		return;
	else
		arr._arr[index] = value;
}





int main()
{
	int M;
	std::cin >> M;
	
	Array A(M);
	for (int i = 0; i < M; i++)
	{
		int p;
		std::cin >> p;
		array_set(A, i, p);
	}
	int ch = 0;

	for (int i = 1; i < M; i++)
	{
		if ((array_get(A, i - 1) >= 0) != (array_get(A, i) >= 0))
		{
			ch++;
		}
	}
	std::cout << ch;
}