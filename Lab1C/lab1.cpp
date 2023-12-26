#include <iostream>
#include <ctime>
#include "array.h"

using namespace std;

Data array_CountValue(Array* arr, Data value)
{
	Data CountValue = 0;
	for (size_t i = 0; i < array_size(arr); i++)
	{
		if (value == array_get(arr, i))
		{
			CountValue++;
		}
	}
	return CountValue;
}

void array_SwapValue(Array* arr, size_t FirstIndex, size_t SecondIndex)
{
	Data number = array_get(arr, FirstIndex);
	array_set(arr, FirstIndex, array_get(arr, SecondIndex));
	array_set(arr, SecondIndex, number);
}

void Task1(Array* arr)
{
	size_t size = array_size(arr);
	cout << endl;
	if (size % 2 == 1)
	{
		for (size_t i = size - 1, k = 0; i != k; i--, k++)
		{
			array_SwapValue(arr, i, k);
		}
	}
	else
	{
		for (size_t i = size - 1, k = 0; k < i; i--, k++)
		{
			array_SwapValue(arr, i, k);
		}
	}

}

void Task2(Array* arr)
{
	cout << endl;

	Data MaxCount = 1;
	Data MaxValueCount = 0;
	bool Uniqueflag = true;
	for (size_t i = 0; i < array_size(arr); i++)
	{
		Data Count = array_CountValue(arr, array_get(arr, i));
		if (MaxCount < Count)
		{
			Uniqueflag = false;
		}
		if (Count >= MaxCount)
		{
			MaxCount = Count;
			MaxValueCount = array_get(arr, i);
		}
	}
	if (Uniqueflag == true)
	{
		cout << "Все элементы уникальны ";
	}
	else
	{
		cout << "Число: " << MaxValueCount << " Встречалось максимальное число раз";
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand((int)time(NULL));

	size_t size;
	Array* arr;
	cout << "Введите размер массива: ";
	cin >> size;

	arr = array_create(size);
	cout << "Задание 1: " << endl;
	size = array_size(arr);
	cout << "Массив: " << endl;
	for (size_t i = 0; i < size; i++)
	{
		array_set(arr, i, rand() % 101);
		cout << array_get(arr, i) << " ";
	}
	Task1(arr);
	cout << "Обратный массив: " << endl;
	for (size_t i = 0; i < array_size(arr); i++)
	{
		cout << array_get(arr, i) << " ";
	}

	array_delete(arr);
	cout << endl << endl;

	arr = array_create(size);
	cout << "Задание 2: " << endl;
	cout << "Массив: " << endl;
	for (size_t i = 0; i < size; i++)
	{
		array_set(arr, i, rand() % 11);
		cout << array_get(arr, i) << " ";
	}
	Task2(arr);
	array_delete(arr);
	cout << endl;
	return 0;
}
