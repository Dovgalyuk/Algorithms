#include <iostream>
#include <ctime>
#include "array.h"



using namespace std;

int counting(Array* arr)
{
	int shet = 0;
		for (int i = 0; i < array_size(arr); i++)
	{
		array_set(arr, i, rand() % 51);
		if (array_get(arr, i) % 2 == 0)
		{
			shet++;
		}
	}
	return shet;
}

void completion(Array* arr, Array* arr2)
{
	int shet = 0;
	for (int i = 0; i < array_size(arr); i++)
	{
		if (array_get(arr, i) % 2 == 0)
		{
			array_set(arr2, shet, i);
			shet++;
		}
	}
}



int main()
{
    setlocale(LC_ALL, "RU");
    srand(time(NULL));
    int size;
    cout << "Введите длину массива: ";
    cin >> size;
	Array* mass = array_create(size); //создаём первый массив с заданным размером

	int size2 = counting(mass); // заполняем первый массив, считая при этом кол-во четных

	Array* mass2 = array_create(size2);// создаём второй массив с размером раным кол-ву четных значений из первого

	completion(mass, mass2);// заполняем второй массив

	for (int i = 0; i < size2; i++) //вывод индексов четных значений среди элементов первого массива
	{
		cout << array_get(mass2, i) << " , ";
	}
	
	array_delete(mass);
	array_delete(mass2);
}
