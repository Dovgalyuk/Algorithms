#include <iostream>
#include "array.h"

using namespace std;

void ArrRandFill(Array* arr)
{
	for (size_t i = 0; i < array_size(arr); i++)
		array_set(arr, i, rand() % 201 - 100);
}

void ArrPrint(Array* arr)
{
	for (size_t i = 0; i < array_size(arr); i++)
		cout << array_get(arr, i) << " ";
	cout << endl;
}

int ArrCheck(Array* arr)
{
	int count = 0;
	for (size_t i = 0; i < array_size(arr); i++)
		for (Data j = 2; j <= 9; j++)
			if (array_get(arr, i) % j == 0)
			{
				count++;
				break;
			}
	return count;
}

int main()
{
	int count;
	size_t ArrSize;
	cout << "Type array size: ";
	cin >> ArrSize;
	Array* arr = array_create(ArrSize);
	ArrRandFill(arr);
	ArrPrint(arr);
	count = ArrCheck(arr);
	cout << "Amount of numbers: " << count;
	array_delete(arr);
	return 0;
}