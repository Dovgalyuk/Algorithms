#include <iostream>
#include "list_test.h"
#include "stack_test.h"
#include "stack.hpp"

int choice(char a, char b);

int main()
{
	std::cout << "List test\n";
	List_test();
	std::cout << "Stack test\n";
	Stack_test();
	std::cout << "\n";
	Stack<char> cont;
	std::string in, out;
	std::cout << "Enter expression to translate:\n";
	std::cin >> in;
	in = in + "|";
	cont.push('|');
	int i = 0;
	while (true)
	{
		if (in[i] >= 'a' && in[i] <= 'z' || in[i] >= 'A' && in[i] <= 'Z')
		{
			out += in[i];
			i++;
		}
		else
		switch (choice(cont.get(), in[i]))
		{
		case 1:
			cont.push(in[i]);
			i++;
			break;
		case 2:
			out += cont.get();
			cont.pop();
			break;
		case 3:
			cont.pop();
			i++;
			break;
		case 4:
			std::cout << "Translation complete:\n";
			std::cout << out;
			return 0;
			break;
		case 5:
		default:
			std::cout << "Translation error. Stoping\n";
			return 1;
			break;
		}
	}
}

int choice(char a, char b)
{
	switch (a)
	{
	case '|':
		switch (b)
		{
		case '|':
			return 4;
			break;
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
			return 1;
			break;
		case ')':
		default:
			return 5;
			break;
		}
		break;
	case '+':
	case '-':
		switch (b)
		{
		case '|':
		case '+':
		case '-':
		case ')':
			return 2;
			break;
		case '*':
		case '/':
		case '(':
			return 1;
			break;
		default:
			return 5;
			break;
		}
		break;
	case '*':
	case '/':
		switch (b)
		{
		case '(':
			return 1;
			break;
		case '|':
		case '+':
		case '-':
		case ')':
		case '*':
		case '/':
			return 2;
			break;
		default:
			return 5;
			break;
		}
	case '(':
		switch (b)
		{
		case ')':
			return 3;
			break;
		case '+':
		case '-':
		case '(':
		case '*':
		case '/':
			return 1;
			break;
		case '|':
		default:
			return 5;
			break;
		}
	default:
		return 5;
		break;
	}
}