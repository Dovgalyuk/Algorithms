#include <iostream>
#include <ctime>
#include "array.h"

using namespace std;
int CheckMaxPrecipitation(Array *array, int period)
{
	int counter = 0;
	int periodSum = 0;
	int periodSumMax = 0;
	int maxPrecipitationPeriod = 0;
	for (int i = 0; i < array_size(array); i++)
	{
		counter += 1;
		periodSum += array_get(array, i);
		if (counter == array_size(array) / period)
		{
			if (periodSum > periodSumMax)
			{
				periodSumMax = periodSum;
				counter = 0;
				maxPrecipitationPeriod = (i + 1) / (array_size(array) / period);
			}
			periodSum = 0;
		}
	}
	return maxPrecipitationPeriod;
}



int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	int randMax = 12500;
	int juneDays;
	cout << "Введите число - размер массива: ";
	cin >> juneDays;
	Array* array = array_create(juneDays);

	for (int i = 0; i < juneDays; i++)
	{
		array_set(array, i, rand() % randMax + 1);
	}

	
	cout << "а) В " << CheckMaxPrecipitation(array,2) << "-ую половину июня выпало больше осадков" << '\n';
	cout << "б) В " << CheckMaxPrecipitation(array,3) << "-ую декаду июня выпало больше осадков" << '\n';
	array_delete(array);
	return 0;
}
