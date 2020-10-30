#include <iostream>
#include"array.h"
#include <cstdlib> 
#include <clocale>
using namespace std;
typedef int Data;
typedef Array<Data> MyArray;
int main()
{
	setlocale(LC_ALL, "RUS");
	int  n;
	cout << "¬ведите число" << endl;
	cin >> n;
	


	srand(4555);
	MyArray*Nas = new MyArray(n);
	for (int i = 0;i < n;i++)
	{
		Nas->set(i, rand()); 
	}
	MyArray* PositiveNas = new MyArray(n);
	for (int i = 0,j=0;i < Nas->size();i++)
	{
		if (Nas->get(i) % 2 == 0)
		{
			PositiveNas->set(j++, i);
		}
	}
	for (int i = 0;i < n;i++)
	{

		if (PositiveNas->get(i)>=0) 
			cout << PositiveNas->get(i) << endl;
	}
}