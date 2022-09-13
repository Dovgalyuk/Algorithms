#include <iostream>
#include <ctime>
#include "array.h"
using namespace std;


int FillingSearching(Array* Parr, int const SIZE)
{
	bool Goood;
	int count = 0,n,m;
	cout << "m:=";
	cin >> m;
	cout << "n:=";
	cin>> n;
	Array* Pbuf = array_create(SIZE);
	int Maxlength = 0;
	array_set(Pbuf, 0, Maxlength);

	for (int i = 0; i < SIZE;)                 //  Заполнение массива рандомными
	{                                          //    НЕ повторяющимеся числами
		Goood = false;
		int RandNumb = rand() % 20;          // Генерация случайного числа от 0 до 100


		for (int j = 0; j < i; j++)             // Проверка на одинаковые числа
		{
			if (array_get(Parr, j) == RandNumb)
			{
				Goood = true;
			}
		}
		if (!Goood)
		{
			if (RandNumb % 2 == 1 && i % 2 == 1) {
				array_set(Parr, i, RandNumb + n - m);
			}
			else if (i % 2 == 1) {
				array_set(Parr, i, RandNumb + n);
			}
			else if(RandNumb % 2 == 1)
				array_set(Parr, i, RandNumb -m);
			else
				array_set(Parr, i, RandNumb);
			cout << array_get(Parr, i) << " | ";
			i++;
		}

	}
	cout << '\n';
	array_delete(Pbuf);
	return Maxlength;
}



int main()
{
	srand(time(NULL));
	int a;
	cout << "Write size arr: ";
	cin >> a;
	cout << "\n\n";
	Array* Parr = array_create(a);
	FillingSearching(Parr, a);


	array_delete(Parr);
	system("pause");
}
