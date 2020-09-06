#include <iostream>
#include "Array.h"

using namespace std;

int main()
{
	int arr_size;
	int maximum;
	int abs_more_max =0;
	setlocale(LC_ALL, "Russian");

	cout << "Введите размер массива =";
	cin >> arr_size;

	Array *arr = array_create(arr_size);

	cout << endl << "Массив :" << endl;
	for(int i=0, j; i< arr_size; i++)
	{
		j=rand()%2001 -1000;
		cout << j << ' ';
		array_set(arr, i, j);
	}

	maximum =array_get(arr, 0);
	for(int i=1; i<arr_size; i++)
	{
		if(array_get(arr, i) > maximum)
			maximum =array_get(arr, i);
	}
	cout << endl << endl << "Максимальный эллемент =" << maximum << endl << endl;

	cout << "Эллементы, по модулю больше максимума :" << endl;
	for(int i=0; i<arr_size; i++)
	{
		if(-array_get(arr, i) > maximum)
		{
			cout << array_get(arr, i) << ' ';
			abs_more_max++;
		}
	}

	cout << endl << endl << "Количество этих эллементов =" << abs_more_max << endl;

	array_delete(arr);
}