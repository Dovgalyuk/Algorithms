#include <iostream>
#include "array.h"
#include <stack.h>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	int  regist_a;
	int  regist_b;
	int  regist_c;
	int  regist_d;
	Stack* stack = stack_create();
	ifstream fileln;
	fileln.open("input.txt");
	ofstream out;
	out.open("output.txt");
	if (!out.is_open() || !fileln.is_open())//проверка открытия файла
	{
		cout << "error!" << endl;
		fileln.close();
		out.close();
		return -1;
	}
	else
	{
		cout << "file open!" << endl;
	}
	return 0;
	
	string str;
	const string str_push = "PUSH";
	const string str_pop = "POP";
	string str_num;
	str_num = "";

	while (fileln.eof())
	{
		getline(fileln, str);//извлечение строк
		for (int i = 0; i < str.length() - str_push.length(); i++)
		{
			if (str.substr(i, str_push.length()) == str_push)
			{
				for (i += str_push.length() + 1; str[i] != ' '; i++)
				{
					str_num.push_back(str[i]);

				}
				stack_push(stack, atoi(str_num.c_str()));
			}
			if (str.substr(i, str_pop.length()) == str_pop)
			{
				i += str_pop.length() + 1;
				switch (str[i])
				{
				case 'A':
					regist_a = stack_get(stack);
					break;
				case 'B':
					regist_b = stack_get(stack);
					break;
				case 'C':
					regist_c = stack_get(stack);
					break;
				case 'D':
					regist_d = stack_get(stack);
					break;
				}
				stack_pop(stack);
			}

			if (out.is_open())
			{
				getline(std::cin, str);
			}
			if (out.is_open()) {
				cout << "A=" << regist_a;
				cout << "B=" << regist_b;
				cout << "C=" << regist_c;
				cout << "D=" << regist_d;
			}
		}
	}
	fileln.close();//освобождение ресурсов
	return 0;
}