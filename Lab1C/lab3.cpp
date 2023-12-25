﻿#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <string>
#include <fstream> 
#include <iostream>
using namespace std;

int main() {
	int stroki=0, dlstrok;
	string lab[100];
	string way,strbuf ;

	cout << "Enter the way to the file: ";
	getline(cin, way);
	cout << "\n"; // C:\Users\iga\Desktop\test.txt
	ifstream file(way);
	if (!file.is_open())
	{
		cout << "\nMistake! The path  ( " << way << " )  is not found!\n";
		return 0;
	}
	else
	{
		while (!file.eof())
		{
			
			++stroki;
			for(int i=0;i<strbuf.length();i++) {
				getline(file, strbuf);
				lab[i] += strbuf;
							   }
		}
	}
	file.close();
	strbuf.clear();

	for (int a = 0; a < stroki; a++)
	{
		cin >> lab[a];
	}
	char z;
	int count = 1;
	
	Queue* x;
	x = queue_create();
	Queue* y;
	y = queue_create();
	dlstrok = lab[0].length();
	for (int a = 0; a < stroki; a++)
		for (int b = 0; b < dlstrok; b++)
		{
			z = lab[a][b];
			if (z == 'X')
			{
				queue_insert(x, b);
				queue_insert(y, a);	
				break;
			}
		}
	
	while (!queue_empty(x))
	{
		Data x1 = queue_get(x);
		queue_remove(x);

		Data y1 = queue_get(y);
		queue_remove(y);

		if (y1+1 <= stroki && lab[y1+1][x1] == '.')
		{
			queue_insert(x, x1);
			queue_insert(y, y1+1);
			lab[y1 + 1][x1] = 'X';
			count++;
		}
		if ((y1-1) >= 0 && lab[y1 - 1][x1] == '.')
		{
			queue_insert(x, x1);
			queue_insert(y, y1 - 1);
			lab[y1 - 1][x1] = 'X';
			count++;
		}
		if ((x1+1) <= dlstrok && lab[y1][x1+1] == '.')
		{
			queue_insert(x, x1+1);
			queue_insert(y, y1);
			
			lab[y1][x1 + 1] = 'X';
			count++;

		}
		if ((x1 - 1) >= 0 && lab[y1][x1 - 1] == '.')
		{
			queue_insert(x, x1 - 1);
			queue_insert(y, y1);
			lab[y1][x1 - 1] = 'X';
			count++;

		}
	}
	cout << count;
	cout << "\n";
	for (int a = 0; a < stroki; a++)
	{
		for (int b = 0;  b < dlstrok; b++)
			cout << lab[a][b];
		cout << "\n";
	}
	queue_delete(x);
	queue_delete(y);
}
