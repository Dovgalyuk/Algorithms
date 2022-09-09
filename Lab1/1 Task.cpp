#include <iostream>
#include <ctime>
#include "array.h"
using std::cin; using std::cout;


int FillingSearching(Array *Parr,  int const SIZE)
{
	bool Goood;
	int count = 0;

	Array *Pbuf = array_create(SIZE);
	int Maxlength = 0;

	array_set(Pbuf, 0, Maxlength);

	for ( int i = 0; i < SIZE;)                 //  Заполнение массива рандомными
	{                                          //    НЕ повторяющимеся числами
		Goood = false;
		int RandNumb = rand() % 101;          // Генерация случайного числа от 0 до 100


		for ( int j = 0; j < i; j++)             // Проверка на одинаковые числа
		{
			if (array_get(Parr,j) == RandNumb)
			{
				Goood = true;
			}
		}

		if (!Goood)
		{
			array_set(Parr, i, RandNumb);
			cout << array_get(Parr, i) << " | ";
			i++;
		}
		
	}

	for (int i = 0; i < SIZE; i++)
	{
	

		if ((array_get(Parr, i) % 2 == 1) || ((array_get(Parr, i) % 2 == 1)) && ((array_get(Parr, i+1) % 2 == 1)))
		{
			++count;                                                              // Увеличиваем счетчик
			array_set(Pbuf, i, count);                                            // Заносим значение в буфер
		}
		else
		{
			count = 0;                                                            // Обнуляем счетчик, если не нечетное значение
		}

		if (array_get(Pbuf, i) > Maxlength)                                      // Ищем наибольшее значение длины нечетных чисел в буфере
		{
			Maxlength = array_get(Pbuf, i);
		}
	}
	cout << "\n\nНаибольший отрезок нечетных чисел в массиве: " << Maxlength << "\n\n";
  
	array_delete(Pbuf);
	return Maxlength;
}



int main()
{
    setlocale(LC_ALL, "RU");
	srand(time(NULL));
    int input;
    cout << "Введите длину массива: ";
    cin >> input;
	cout << "\n\n";
 
	Array  *Parr = array_create(input);
	FillingSearching(Parr, input);
	

	array_delete(Parr);
	system("pause");
}


