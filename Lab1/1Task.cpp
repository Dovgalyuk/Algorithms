#include <iostream>
#include <ctime>
#include "array.h"
using std::cin; using std::cout;


int FillingSearching(Array *Parr,  int const SIZE)
{
	bool Goood;
	int count = 0, Maxlength = 0;

	for (int i = 0; i < SIZE; i++)
	{  
		array_set(Parr, i,  rand() % 101);                       // Генерация случайного числа от 0 до 100
		cout << array_get(Parr, i) << " | ";                    //  Вывод сгенерированного массива на экран

		if (array_get(Parr, i) % 2 != 0)                      // Если элемент массива нечетный, то
		{
			++count;                                        // Увеличиваем счетчик       
			                                       
		}
		else               
		{
			count = 0;                                 // Обнуляем счетчик
		}
		if (Maxlength < count)
		{
			Maxlength = count;
		}

	}
	cout << "\n\nНаибольший отрезок нечетных чисел в массиве: " << Maxlength << "\n\n";
  
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
	//system("pause");
}
