#include <iostream>
#include "array.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	int arr_size;
<<<<<<< HEAD
	int i, n;
=======
>>>>>>> master
	int positive = 0;
	int negative = 0;

	setlocale(LC_ALL, "Russian");

	cout << "¬ведите размер массива =";
	cin >> arr_size;
	Array* arr = array_create(arr_size);
	cout << "массив" << endl;
<<<<<<< HEAD
		for (int i = 0, n; i < arr_size; i++)
		{
			n = rand() % 201 - 100;
			cout << n << ' ';
			array_set(arr, i, n);
		}
	for (int i = 0; i < arr_size; i++)
	{
		if (array_get(arr, i) < 0)
=======
	for (int i = 0, n; i < arr_size; i++)
	{
		n = rand() % 201 - 100;
		cout << n << ' ';
		array_set(arr, i, n);
	}
	for (int i = 0; i < arr_size; i++)
	{
		if (array_get(arr, i) >= 0)
>>>>>>> master
			positive++;
		else
			negative++;
	}

	Array* mas1 = array_create(positive);
	Array* mas2 = array_create(negative);
	positive = 0;
<<<<<<< HEAD
    negative = 0;
		for (int i = 0; i < arr_size; i++)
		{
			if (array_get(arr, i) >= 0)
			{
				array_set(mas1, positive, array_get(arr, i)) ;
				positive++;
			}
			else
			{
				array_set(mas2, negative, array_get(arr, i));
				negative++;
			}

			printf("\n");
			for (i = 0; i < positive; i++) printf("%3d", array_get(mas1, i));
			printf("\n");
			for (i = 0; i < negative; i++) printf("%3d", array_get(mas2, i));
			printf("\n");
		}
		array_delete(arr);
		array_delete(mas1);
		array_delete(mas2);
=======
	negative = 0;
	for (int i = 0; i < arr_size; i++)
	{
		if (array_get(arr, i) >= 0)
		{
			array_set(mas1, positive, array_get(arr, i));
			positive++;
		}
		else
		{
			array_set(mas2, negative, array_get(arr, i));
			negative++;
		}
}
		printf("\n");
		for (int i = 0; i < positive; i++) printf("%3d", array_get(mas1, i));
		printf("\n");
		for (int i = 0; i < negative; i++) printf("%3d", array_get(mas2, i));
	
		printf("\n");
	
	array_delete(arr);
	array_delete(mas1);
	array_delete(mas2);
>>>>>>> master
}