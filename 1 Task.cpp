#include <iostream>
#include <ctime>
using std::cin; using std::cout;


int FillingSearching(int  *Parr,  int const SIZE)
{
	bool Goood;
	int count = 0;
	int *Pbuf  = new int [SIZE];
	int Maxlength = 0;
	*Pbuf = Maxlength;

	for ( int i = 0; i < SIZE;)                 //  Заполнение массива рандомными
	{                                          //    НЕ повторяющимеся числами
		Goood = false;
		int RandNumb = rand() % 101;          // Генерация случайного числа от 0 до 100


		for ( int j = 0; j < i; j++)             // Проверка на одинаковые числа
		{
			if (Parr[j] == RandNumb)
			{
				Goood = true;
			}
		}

		if (!Goood)
		{
			Parr[i] = RandNumb;
			cout << Parr[i] << " | ";
			i++;
		}
	}

	for (int i = 0; i < SIZE; i++)                
	{

		if ((Parr[i] % 2 == 1) || ((Parr[i] % 2 == 1) && (Parr[i + 1] % 2 == 1)))          
		{
			++count;                                                              // Увеличиваем счетчик
			Pbuf[i] = count;                                                      // Заносим значение в буфер
		}
		else
		{
			count = 0;                                                            // Обнуляем счетчик, если не нечетное значение
		}

		if (Pbuf[i] > Maxlength)                                                    // Ищем наибольшее значение длины нечетных чисел в буфере
		{
			Maxlength = Pbuf[i];
		}
	}
	cout << "\n\nНаибольший отрезок нечетных чисел в массиве: " << Maxlength << "\n\n";
    delete[] Pbuf;
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
    int *Parr = new int [input];

	FillingSearching(Parr, input);
	
    delete[] Parr;
	system("pause");
}


