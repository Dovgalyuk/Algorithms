#include "array.h"
#include <iostream>
#include <ctime>
using namespace std;

int main()
{

	int arr_size, counter = 0, num1 = 0, num2;

	cout << "Enter array size: ";
	cin >> arr_size;
	Array* arr = array_create(arr_size);

	srand(time(NULL));
	cout << "Array: ";
	for (int i = 0; i < arr_size; i++) {
		array_set(arr, i, 1 + rand() % 10);
		cout << array_get(arr, i) << " ";
	}

	cout << endl << "Element repeated 2 times: ";

	for (int i = 0; i < arr_size; i++, counter = 0)
	{
		for (int j = 0; j < arr_size; j++)
			if (array_get(arr, i) == array_get(arr, j))
				counter++;
		if (counter == 2)
		{
			num2 = num1;
			num1 ^= array_get(arr, i);
			if (num2 > num1)
				cout<< array_get(arr, i) <<" ";
		}

	}
	array_delete(arr);
}