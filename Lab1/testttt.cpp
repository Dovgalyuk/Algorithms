#include <iostream>
#include <ctime>
#include "array.h"

using std::cin;
using std::cout;
using std::endl;

void task1(Array* Numbers)
{
	int kpol=0;
	int kotr=0;
	int sumpol=0;
	int sumotr=0;
	int size = array_size(Numbers);
	cout << "Полученный массив:" << endl;
	for (int i = 0; i < size; i++)
	{
		array_set(Numbers, i, rand() % 201 - 100);
		cout << array_get(Numbers, i) << " ";
	}
	for (int i = 0; i < size; i++)
	{
		if (array_get(Numbers, i) > 0)
		{
			kpol++;
			sumpol+= array_get(Numbers, i);
		}
		if (array_get(Numbers, i) < 0)
		{
			kotr++;
			sumotr+= array_get(Numbers, i);
		}
	}
	cout << endl << endl << "Среднее арифметическое положительных элементов: " << (float)sumpol / kpol << endl;
	cout << "Среднее арифметическое отрицательных элементов: " << (float)sumotr / kotr << endl;
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));

	int k;
	cout << "Введите размер массива: ";
	cin >> k;
	cout << endl;

	Array *Numbers = array_create(k);

	task1(Numbers);
	
	array_delete(Numbers);
	system("pause");
}
