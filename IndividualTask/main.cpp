#include <iostream>
#include <ctime>
#include "array.h"

using namespace std;

void print(Array* arr, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << array_get(arr, i) << " ";
	}
	cout << endl;
}

void fill(Array* arr, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		array_set(arr, i, rand() % 201 - 100);
	}
}

void search_low_avg(Array* arr, size_t size)
{
	Data sum = 0;
	for (size_t i = 0; i < size; i++)
	{
		sum += array_get(arr, i);
	}
	Data avg = sum/size;
	for (size_t i = 0; i < size; i++)
	{
		Data temp = array_get(arr, i);
		if (temp < avg)
		{
			cout << temp;
		}
	}
}

int main()
{
	size_t size = 0;
	cout << "Enter the size of array: ";
	cin >> size;
	cout << endl;

	Array* arr = array_create(size);
	fill(arr, size);
	search_low_avg(arr, size);
	array_delete(arr);
	return 0;
}