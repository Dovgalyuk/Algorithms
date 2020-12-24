#include <iostream>
#include "array.h"
using namespace std;

int main()
{
	size_t size;
	cout << "Enter array size: ";
	cin >> size;
	Array* array = array_create(size);
	
	long long summ = 0;
	long long proizv = 1;
	for (int i = 0; i < size; i++)
	{
		int random_number = rand();
		array_set(array, i, random_number);
		summ += random_number;
		proizv *= random_number;
	}

	cout << "Array elements: ";
	for (int i = 0; i < size; i++)
	{
		cout << array_get(array, i) << " ";
	}
	cout << endl << "Sum of elements : " << summ << endl;
	cout << "Multiplication: " << proizv;
}