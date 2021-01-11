#include <iostream>
#include "stack.h"
using namespace std;

int main()
{
	size_t stack_size;
	cout << "Enter stack size: ";
	cin >> stack_size;

	Stack* stack = stack_create();
	size_t current_size = 0;

	cout << "Enter commands or \"end\" to quit: " << endl;
	while (true)
	{
		string command;
		int N = 0;
		cin >> command;
		if (command == "end")
		{
			break;
		}
		else if (command == "push")
		{
			if (current_size >= stack_size)
			{
				cout << "BAD PUSH" << endl;
				continue;
			}
			else
			{
				cin >> N;
				stack_push(stack, N);
				current_size++;
			}
		}
		else if (command == "pop")
		{
			if (stack_empty(stack))
			{
				cout << "BAD POP" << endl;
				continue;
			}
			else
			{
				cout << stack_get(stack) << endl;
				stack_pop(stack);
				current_size--;
			}
		}
	}

	cout << "STACK" << endl;
	while (!stack_empty(stack))
	{
		cout << stack_get(stack) << endl;
		stack_pop(stack);
	}
	
	stack_delete(stack);
}