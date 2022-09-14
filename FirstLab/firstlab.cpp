#include <iostream>
#include <ctime>
#include "array.h"
using std::cin; using std::cout;

int ArrayProcessing(Array* ARR, int const &SIZE)
{
	int count = 0, max = array_get(ARR, 0), index1 = 0, index2 = 0;
	bool Flag;
	for (int i = 0; i < SIZE; i++)
	{
		array_set(ARR, i, rand() % 101);
		cout << array_get(ARR, i) << " ";

		if (array_get(ARR, i) > max)
		{
			max = array_get(ARR, i);
			index1 = i;
			Flag = false;
		}
		else if (array_get(ARR, i) >= max)
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

	return max;
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
	ArrayProcessing(ARR, length);

	array_delete(ARR);
	system("pause");
}
