#include <iostream>
#include <ctime>
#include "array.h"

using namespace std;

void print(Array* arr)
{
	for (int i = 0; i < array_size(arr); i++)
		cout << "arr[" << i << "]= " << array_get(arr, i) << endl;
	cout << endl;
}

void fill(Array* arr)
{
	for (int i = 0; i < array_size(arr); i++)
		array_set(arr, i, rand() % 201 - 100);
}

void search_low_avg(Array* arr)
{
	int i;
	float sum;
	sum = i = 0;
	for (i; i < array_size(arr); i++)
		sum += array_get(arr, i);
	cout << "The sum of elements is: " << sum << endl;
	double avg = sum / i;
	cout << "The avg of elements is: " << avg << endl;
	cout << "The elements satisfying for condition: " << endl;
	for (i = 0; i < array_size(arr); i++)
	{
		if (array_get(arr, i) < avg)
			cout << "arr[" << i << "]= " << array_get(arr, i) << endl;
	}
}

int main()
{
	size_t size = 0;
	cout << "Enter the size of array: ";
	cin >> size;
	cout << endl;
	
	Array* arr = array_create(size);
	fill(arr);
	print(arr);
	search_low_avg(arr);
	array_delete(arr);
	return 0;
}