#include <iostream>
#include <ctime>
#include "array.h"

using namespace std;

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	int randMax = 12500;
	int juneDays;
	cout << "Введите число - размер массива: ";
	cin >> juneDays;
	Array *array = array_create(juneDays);
	for (int i = 0; i < juneDays; i++)
	{
		array_set(array,i,rand() % randMax + 1);
	}
	int halfPart = 0;
	int halfSum = 0;
	int maxHalfSum = halfSum;
	int counter = 0;
	for (int i = 0; i < juneDays; i++)
	{
		counter += 1;
		halfSum += array_get(arr,i);
		if (counter == juneDays / 2)
		{
			if (halfSum > maxHalfSum)
			{
				maxHalfSum = halfSum;
				counter = 0;
				halfPart = (i+1) / (juneDays / 2);
			}
			halfSum = 0;
		}
	}
	int decadePart = 0;
	int decadeSum = 0;
	int maxDecadeSum = decadeSum;
	counter = 0;
	for (int i = 0; i < juneDays; i++)
	{
		counter += 1;
		decadeSum += array_get(arr,i);;
		if (counter == juneDays / 3)
		{
			if (decadeSum > maxDecadeSum)
			{
				maxDecadeSum = decadeSum;
				counter = 0;
				decadePart = (i+1) / (juneDays / 3);
			}
			decadeSum = 0;
		}
	}

	cout << '\n' << '\n' << "а) В " << halfPart << "-ую половину июня выпало больше осадков" << '\n';
	cout << "б) В " << decadePart << "-ую декаду июня выпало больше осадков" << '\n';
	array_delete(arr);
	return 0;
}
