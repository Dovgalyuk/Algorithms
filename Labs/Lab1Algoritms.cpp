

#include <iostream>
#include "array.h"
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	int size;
	int sum = 0;
	int composition = 1;
	Data putArray; 
	cin >> size;
	Array* arr = array_create(size);
	for (int i = 0; i < size; i++)
	{
		cin >> putArray;
		array_set(arr, i, putArray);
	}
	

	for (int i = 0; i <size; i++)
	{
		composition *= array_get(arr, i);
		sum += array_get(arr, i);

	}
	cout <<"Сумма " << sum << ' ' << "Произведение " << composition;
}

