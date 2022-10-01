#include <iostream>
#include <ctime>
#include "array.h"
using namespace std;


void FillingSearching(Array* Parr, int const SIZE)
{
	int counter_zero = 0, counter_positive = 0, counter_negative = 0;

	for (int i = 0; i < SIZE; i++)
	{
		array_set(Parr, i, -100 + rand() % (201));                       // Генерация случайного числа от -100 до 100
		cout << array_get(Parr, i) << " | ";                    //  Вывод сгенерированного массива на экран

		if (array_get(Parr, i) == 0)                      
		{
			counter_zero++;                                               
		}
		if (array_get(Parr, i) < 0)
		{
			counter_negative++;
		}
		if (array_get(Parr, i) > 0)
		{
			counter_positive++;                                 
		}

	}
	cout << "\n\nКол-во положительных чисел в массиве: " << counter_positive << "\n\n";
	cout << "\n\nКол-во отрицательных чисел в массиве: " << counter_negative << "\n\n";
	cout << "\n\nКол-во нулевых значений в массиве: " << counter_zero << "\n\n";
}



int main()
{
	setlocale(LC_ALL, "RU");
	srand(time(NULL));
	int input;
	cout << "Введите размер массива: ";
	cin >> input;
	cout << "\n\n";

	Array* Parr = array_create(input);
	FillingSearching(Parr, input);


	array_delete(Parr);
	system("pause");
}