#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
	Stack* data = stack_create();
	int size, items;
	cin >> size;
	items = 0;
	while (!std::cin.eof())
	{
		string command;
		cin >> command;
		int nomber;
		if (command == "push")
			cin >> nomber;
		if (command == "push")
			if (items + 1 > size)
				cout << "BAD PUSH\n";
			else
			{
				items++;
				stack_push(data, nomber);
			}
		else
			if (command == "pop")
				if (items <= 0)
					cout << "BAD POP\n";
				else
				{
					cout << stack_get(data) << '\n';
					items--;
					stack_pop(data);
				}
	}
	cout << "STACK\n";
	while (items > 0)
	{
		cout << stack_get(data) << '\n';
		items--;
		stack_pop(data);
	}
	stack_delete(data);
}