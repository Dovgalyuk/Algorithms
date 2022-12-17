#include <iostream>
#include "array.h"

using namespace std;

int main()
{
	int a, max = -1, id_1, id_2 = 0;
	Array* A = NULL;
	//Вводим размер массива
	cin >> a;
	A = array_create(a);
	for (int i = 0; i < a; i++)
	{
		//Задаём случайные числа от 0 до 150
		array_set(A, i, rand() % 151);
	}

	// В цикле проходим все элементы массива
	for (int i = 0; i < a; i++)
	{
		// Если эдемент массива больше max, запоминаем его 
		if (array_get(A, i) > max)
		{
			id_1 = i;
			max = array_get(A, i);
			// Сбрасываем второй id до нуля, чтобы его случайно не вывести 
			id_2 = 0;
		}
		// Если равен max, запоминаем его во второй id
		else if (array_get(A, i) == max)
			id_2 = i;
	}
	// Если второй id равен 0 (в массиве только 1 максимальная скорость), условие вернёт false, иначе true
	if (id_2)
	{
		//Добавляем единицу, чтобы вывести порядковый номер
		cout << id_1 + 1 << " " << id_2 + 1;
	}
	else
		//Добавляем единицу, чтобы вывести порядковый номер
		cout << id_1 + 1;
	//Очищаем память
	array_delete(A);
}
