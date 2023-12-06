#include <iostream>

using namespace std;
#include <ctime>

#include "array.h"

void print_data(Array* arr) {
	for (size_t i = 0; i < array_size(arr); i++) {
		cout << array_get(arr, i) << " ";
	}
	cout << endl;
}

Array* random_full() {
	size_t size;
	cin >> size;
	Array* newArray = NULL;
	newArray = array_create(size);
	for (size_t i = 0; i < size; i++) {
		array_set(newArray, i, 1 + rand() % 10);
	}
	
	return newArray;
}

Array* delete_elements() {
	Array* newArray = NULL;
	Array* oldArray = NULL;
	/*Array* anotherone = NULL;*/
	newArray = random_full();
	print_data(newArray);

	int no_need_element = 0;
	int n;
	int m;
	cin >> n;
	cin >> m;

	for (size_t i = 0; i < array_size(newArray); i++) 
	{
		if (array_get(newArray, i) >= n && array_get(newArray, i) <= m) 
		{
			array_set(newArray, i, 0);
		}
	}
	
	for (size_t i = 0; i < array_size(newArray) - 1; i++)
	{

		for (size_t j = 0; j < array_size(newArray) - i - 1; j++)
		{
			if (array_get(newArray, j) < array_get(newArray, j + 1))
			{
				int temp = array_get(newArray, j);
				array_set(newArray, j, array_get(newArray, j + 1));
				array_set(newArray, j + 1, temp);
			}
		}
	}

	for (size_t i = 0; i < array_size(newArray); i++) 
	{
		if (array_get(newArray, i) == 0)
		{
			no_need_element++;
		}
	}

	oldArray = array_create(array_size(newArray) - no_need_element);

	for (size_t i = 0; i < array_size(oldArray); i++)
	{
		array_set(oldArray, i, array_get(newArray, i));
		cout << i ;
	}
	cout << endl;

	/*anotherone = array_create(array_size(oldArray) + no_need_element);

	for (size_t i = 0; i < array_size(oldArray); i++)
	{
		array_set(anotherone, i, array_get(oldArray, i));
	}

	for (size_t i = (array_size(newArray) - no_need_element); i < array_size(anotherone); i++)
	{
		array_set(anotherone, i, 0);
	}*/

	/*array_delete(newArray);
	array_delete(oldArray);*/
	/*return oldArray;*/ // Можно раскоментить return и закоментить array_delete(oldArray), чтобы глянуть, что элементы удаляются
	return newArray;
}


void sum_elements() {
	Array* newArray = NULL;
	newArray = random_full();

	print_data(newArray);

	int sum = 0;

	for (size_t i = 0; i < array_size(newArray); i++) {
		if (array_get(newArray, i) % 2 == 0 && array_get(newArray, i) > 0) 
		{
			sum += array_get(newArray, i);
		}
	}

	cout << sum;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	//РАСКОМЕНТИРОВАТЬ

	/*cout << "Рандомный массив" << endl;
	Array* a = NULL;
	a = random_full();
	
	array_delete(a);
	print_data(a);*/
	
	

	cout << "Введите количество элементов массива, затем выберите интервал двумя числами" << endl;
	Array* b = NULL;
	b = delete_elements();
	print_data(b);
	array_delete(b);
	

	/*cout << "Введите количество элементов массива, выводит сумму четных" << endl;
	Array* c = NULL;
	sum_elements();
	print_data(c);
	array_delete(c);*/

	return 0;
}