#include <iostream>
#include "array.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int size;
	int positive = 0, negative = 0, zero = 0;

	cout << "¬ведите размер массива : ";
	cin >> size;
	Array* arr = array_create(size);

	cout << endl << "ћассив : " << endl;
	for (int i = 0, x; i < size; i++)
	{
		x = rand() % 201 - 100;     // диапазон[-100;100]
		cout << x << ' ';
		array_set(arr, i, x);
		if (x > 0)
			positive++;
		if (x < 0)
			negative++;
		if (x == 0)
			zero++;
	}

	cout << endl << endl << "¬ массиве содержитс€ [" << positive << "] положительных, [" << negative << "] отрицательных и [" << zero << "] нулевых значений. " << endl;

	array_delete(arr);

	return 0;
}