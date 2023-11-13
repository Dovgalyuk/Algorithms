#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <string>
#include <iostream>
using namespace std;

int main() {
	int stroki, dlstrok;
	cout << "vveditecolvo strok";
	cin >> stroki;
	string lab[100]; 
	for (int a = 0; a < stroki; a++)
	{
		cin >> lab[a];
	}
	

	char z;
	int count = 1;
	int kordinata = 0;
	dlstrok = lab[0].length();
	for (int a = 0; a < stroki; a++)
		for (int b = 0; b < dlstrok; b++)
		{

			z = lab[a][b];

			if (z == 'X')
			{
				kordinata = a * 10 + b;

				break;
			}
		}
	Queue* a;
	a = queue_create();
	Data p;
	
	p = kordinata;
	queue_insert(a, p);
	while (1)
	{

		Data z = queue_get(a);

		queue_remove(a);
		if ((z / 10 + 1) <= 4 && lab[z / 10 + 1][z % 10] == '.')
		{
			
			p = z + 10;

			queue_insert(a, p);
			lab[z / 10 + 1][z % 10] = 'X';
			count++;
		}
		if ((z / 10 + 1) >= 0 && lab[z / 10 - 1][z % 10] == '.')
		{
		

			p = z - 10;

			queue_insert(a, p);
			lab[z / 10 + 1][z % 10] = 'X';
			count++;
		}
		if ((z % 10 + 1) <= 5 && lab[z / 10][z % 10 + 1] == '.')
		{
			

			p = z + 1;
			queue_insert(a, p);
			lab[z / 10][z % 10 + 1] = 'X';
			count++;

		}
		if ((z % 10 - 1) >= 0 && lab[z / 10][z % 10 - 1] == '.')
		{
			
			p = z - 1;
			queue_insert(a, p);
			lab[z / 10][z % 10 - 1] = 'X';
			count++;

		}
		if (queue_empty(a))
			break;

	}
	cout << count;
	cout << "\n";
	for (int a = 0; a < 5; a++)
	{

		for (int b = 0; b < 6; b++)


			cout << lab[a][b];
		cout << "\n";
	}
	queue_remove(a);
}
