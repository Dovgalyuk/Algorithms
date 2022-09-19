#include <iostream>
#include <ctime>
#include "array.h"
using std::cin; using std::cout;

int ArrayProcessing(Array* ARR)
{
	int count = 0, index1 = 0, index2 = 0;
	bool Flag = false;

	int size = array_size(ARR);

	for (int i = 0; i < size; i++)
	{
		array_set(ARR, i, rand() % 101);
		int max = array_get(ARR, 0);
		cout << array_get(ARR, i) << " ";

		if (array_get(ARR, i) > max)
		{
			max = array_get(ARR, i);
			index1 = i;
			Flag = false;
		}
		else if (array_get(ARR, i) == max)
		{
			max = array_get(ARR, i);
			index2 = i;
			Flag = true;
		}

	}
	if (Flag)
	{
		cout << "\n\nПервая встреченная машина с макс скоростью и ее номер: " << index1 << "\n";
		cout << "\n\nНомер последней машины с макс скоростью: " << index2 << "\n\n";
	}
	else
	{
		cout << "\n\nПервая встреченная машина с макс скоростью и ее номер: " << index1 << "\n\n";
	}
}

int main()
{
	setlocale(LC_ALL, "RU");
	srand(time(NULL));
	int length;
	cout << "Введите длину массива: ";
	cin >> length;
	cout << "\n\n";

	Array* ARR = array_create(length);
	ArrayProcessing(ARR);

	array_delete(ARR);
	system("pause");
}
