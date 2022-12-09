#include <iostream>
#include <ctime>
#include "array.h"
using namespace std;


void FillSearch(Array* Parr, int const SIZE)
{
	bool Good;
	int count = 0, Maxlength = 0;

	for (int i = 0; i < SIZE; i++)
	{
		array_set(Parr, i, rand() % 101);
		cout << array_get(Parr, i) << " ";
	}

		int max = array_get(Parr, 0);
		for (int i = 0; i < SIZE; i++) {
			if ((i % 2 == 0) && (max < array_get(Parr, i))) {
				max = array_get(Parr, i);
			}
		}
		cout <<endl<< "Максимальный элемент с четным индексом массива : "<<max<<endl;


}



int main()
{
	setlocale(LC_ALL, "RU");
	srand(time(NULL));
	int input;
	cout << "Введите длину массива: ";
	cin >> input;
	cout << "\n";
	Array* Parr = array_create(input);
	FillSearch(Parr, input);
	array_delete(Parr);
	return(0);
	system("pause");

}
