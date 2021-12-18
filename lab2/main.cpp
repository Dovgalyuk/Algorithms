#include "pch.h"
#include <iostream>
#include <fstream>
#include "stack.h"
#include<string>

using namespace std;

int main()
{
	string filename;
	cout << "Enter filename: ";
	cin >> filename;
	fstream file(filename);

	Stack* stack = stack_create();
	while (!file.eof())
	{
		string str;
		file >> str;
		for (int i = 0; i < str.size(); i++)
		{
			stack_push(stack, str[i]);
		}
		while (!stack_empty(stack))
		{
			cout << (char)stack_get(stack);
			stack_pop(stack);
		}
		cout << endl;
	}
}