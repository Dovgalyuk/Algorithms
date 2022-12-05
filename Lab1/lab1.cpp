#include <iostream>
#include "array.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");
	srand(time(NULL));

	int size;
	cout << "Введите длину массива: ";
	cin >> size;

	Array* arr = array_create(size);

	for (int i = 0; i < size; i++) // заполнение
	{
		array_set(arr, i, rand() % 100);
	}

	cout << "Массив: ";
	for (int i = 0; i < size; i++) //  выводим массив
	{
		cout << array_get(arr, i) << " ";
	}
	cout << endl;

	int sumMore20 = 0; 
	int sumLess50 = 0;
	int elem;
	for (int i = 0; i < size; i++) //  перебираем массив
	{
		elem = array_get(arr, i);
		if (elem > 20) 
			sumMore20 += elem;
		if (elem < 50)
			sumLess50 += elem;
	}

	if (sumMore20 > 100) 
		cout << "сумма элементов, которые больше 20, превышает 100 ("<< sumMore20<<")";
	else
		cout << "сумма элементов, которые больше 20, НЕ превышает 100 (" << sumMore20 << ")";

	cout << endl;

	if (sumLess50 % 2 == 0)
		cout << "сумма элементов, которые меньше 50, есть четное число (" << sumLess50 << ")";
	else
		cout << "сумма элементов, которые меньше 50, есть НЕчетное число (" << sumLess50 << ")";
}
