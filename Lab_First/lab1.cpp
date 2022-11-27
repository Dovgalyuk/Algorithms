#include <iostream>
#include <ctime>
#include "array.h"

using namespace std;
void TwoMin(Array* Parr)
{
	int min1 = 100, min2 = 100;

	for (int i = 0; i < array_size(Parr); i++)
	{
		array_set(Parr, i, -50 + rand() % (101));
		cout << array_get(Parr, i) << endl;

		if (array_get(Parr, i) < min1)
		{
			min2 = min1;
			min1 = array_get(Parr, i);
		}
		else if (array_get(Parr, i) < min2)
			min2 = array_get(Parr, i);

	}
	cout << "Первый минимальный элемент: " << min1 << endl;
	cout << "Второй минимальный элемент: " << min2 << endl;
}



int main()
{
	setlocale(LC_ALL, "RU");
	srand(time(NULL));
	int size;
	cout << "Введите размер массива: ";
	cin >> size;
	cout << endl;
	Array* A = array_create(size);
	TwoMin(A);

	array_delete(A);
	system("pause");
}

