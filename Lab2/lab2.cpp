#include <iostream>
#include <string>
#include "stack.h"
#include "list.h"

using std::cin; using std::cout; using std::string; using std::endl;

void Task()
{
	Stack* stack = stack_create();
	string s, s1;
	cout << "¬ведите строку: ";
	getline(cin, s);
	for (int i = 0; i <= s.length(); i++)
	{
			if (s[i] != ' ' && s[i]!='\0') s1 = s1 + s[i];
			else
			{
				if ((s1[0]>=48) && (s1[0]<=57))
				{
					int chislo = stoi(s1);
					stack_push(stack, chislo);
				}
				if (s1 == "dup")
				{
					int chislo = stack_get(stack);
					stack_push(stack, chislo);
				}
				if (s1 == ".")
				{
					cout << stack_get(stack) << endl;
					stack_pop(stack);
				}
				if (s1 == "drop")
				{
					stack_pop(stack);
				}
				if (s1 == "swap")
				{
					int last = stack_get(stack);
					stack_pop(stack);
					int lastt = stack_get(stack);
					stack_pop(stack);
					stack_push(stack,last);
					stack_push(stack,lastt);
				}
				if (s1 == "over")
				{
					int last = stack_get(stack);
					stack_pop(stack);
					int lastt = stack_get(stack);
					stack_push(stack, last);
					stack_push(stack, lastt);
				}
				if (s1 == "rot")
				{
					int last = stack_get(stack);
					stack_pop(stack);
					int lastt = stack_get(stack);
					stack_pop(stack);
					int lasttt = stack_get(stack);
					stack_pop(stack);
					stack_push(stack, lastt);
					stack_push(stack, last);
					stack_push(stack, lasttt);
				}
				if (s1 == "+")
				{
					int last = stack_get(stack);
					stack_pop(stack);
					int lastt = stack_get(stack);
					stack_pop(stack);
					stack_push(stack, last + lastt);
				}
				if (s1 == "-")
				{
					int last = stack_get(stack);
					stack_pop(stack);
					int lastt = stack_get(stack);
					stack_pop(stack);
					stack_push(stack, last - lastt);
				}
				if (s1 == "*")
				{
					int last = stack_get(stack);
					stack_pop(stack);
					int lastt = stack_get(stack);
					stack_pop(stack);
					stack_push(stack, last * lastt);
				}
				if (s1 == "/")
				{
					int last = stack_get(stack);
					stack_pop(stack);
					int lastt = stack_get(stack);
					stack_pop(stack);
					stack_push(stack, last / lastt);
				}
				s1 = "";
			}
	}
	stack_delete(stack);
}

int main()
{
	setlocale(LC_ALL, "ru");
	Task();
	system("pause");
	system("cls");
	main();
}