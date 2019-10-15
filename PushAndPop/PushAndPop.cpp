#include "pch.h"
#include <iostream>
#include "stack.h"
#include <fstream>
#include <string>
using namespace std;

int main()
{
	Stack* stack = stack_create();
	int A = 0, B = 0, C = 0, D = 0;
	ifstream fin("input.txt");

	if (!fin)
	{
		cout << "Unable to open file!/n";
		system("Pause");
		return 0;
	}

	while (!fin.eof())
	{
		string str;
		getline(fin, str);
		if (str[1] == 'U') {
			if (str[5] == 'A' || str[5] == 'B' || str[5] == 'C' || str[5] == 'D')
			{
				if (str[5] == 'A')
				{
					stack_push(stack, A);
				}
				if (str[5] == 'B')
				{
					stack_push(stack, B);
				}
				if (str[5] == 'C')
				{
					stack_push(stack, C);
				}
				if (str[5] == 'D')
				{
					stack_push(stack, D);
				}
			}
			else
			{
				int number = 0, i = 0;
				while (str[5 + i] != '\0')
				{
					int digit = (int)str[5 + i] - (int)'0';
					number = number * 10 + digit;
					i++;
				}
				stack_push(stack, number);
			}

		}
		else
		{
			if (str[4] == 'A')
			{
				A = stack_get(stack);
				stack_pop(stack);
			}
			if (str[4] == 'B')
			{
				B = stack_get(stack);
				stack_pop(stack);
			}
			if (str[4] == 'C')
			{
				C = stack_get(stack);
				stack_pop(stack);
			}
			if (str[4] == 'D')
			{
				D = stack_get(stack);
				stack_pop(stack);
			}
		}
	}

	cout << "A = " << A << endl;
	cout << "B = " << B << endl;
	cout << "C = " << C << endl;
	cout << "D = " << D << endl;

	stack_delete(stack);
	fin.close();

	system("Pause");
	return 0;
}

