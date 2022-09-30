#include <iostream>
#include <ctime>
#include "array.h"
using namespace std;
void FillingSearching(Array* Parr,Array* Parr_count, int const SIZE)
{
	int *arr=new int[SIZE];
	int count, m, n;
	cout << "m:=";
	cin >> m;
	cout << "n:=";
	cin>> n;
	for (int i = 0; i < SIZE; i++)
	{
		array_set(Parr, i, count = rand() % 100);                     
		cout << array_get(Parr, i) << " | ";                   
		array_set(Parr_count, i,count);
	}
	cout << "Отредактированный массив:" << endl;
	for (int i = 0; i < SIZE; i++)
	{
		if(array_get(Parr, i) % 2 != 0&&i%2!=0)
			array_set(Parr, i, array_get(Parr_count, i) - m + n);
		else if (array_get(Parr, i) % 2 != 0)
			array_set(Parr, i, array_get(Parr_count, i) -m);
		else if(i%2!=0)
			array_set(Parr, i, array_get(Parr_count, i) +n);
		cout << array_get(Parr, i) << " | ";
	}
}



int main()
{
	setlocale(LC_ALL, "RU");
	srand(time(NULL));
	int input;
	cout << "Введите длину массива: ";
	cin >> input;
	cout << "\n\n";

	Array* Parr = array_create(input);
	Array* Parr_count = array_create(input);
	FillingSearching(Parr,Parr_count, input);


	array_delete(Parr);
	
	system("pause");
}
