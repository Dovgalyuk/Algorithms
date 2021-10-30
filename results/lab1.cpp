#include <iostream>

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите количество элементов массива:" << endl;
	int n;
	int k = 0;
	cin >> n;
	int* array = new int[n];
	for (int i = 0; i < n; i++) //вводим динамический массив
	{
		cin >> array[i];
	}
	cout << "=========================" << endl;
	cout << "Введенный массив:" << endl;
	for (int i = 0; i < n; i++)//выводим введенный массив 
	{
		cout << array[i] << endl;
	}
	for (int i = 0; i < n - 1; i++) //делаем условие проверки
	{
		if (array[i] * (-1) > 0 && array[i + 1] > 0)
			k++;
		if (array[i] * (-1) < 0 && array[i + 1] < 0)
			k++;
	}
	cout << "Массив меняет знак: " << k << " раза" << endl;
	delete[]array; //очищаем память
}
