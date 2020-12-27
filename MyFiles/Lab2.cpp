#include <iostream>
#include "stack.h"
using namespace std;

void stack_print(Stack* stack)
{
	while (!stack_empty(stack))
	{
		std::cout << stack_get(stack) << "\n";
		stack_pop(stack);
	}
}

int main()
{
	size_t size;
	cout << "Enter stack size: ";
	cin >> size;

	Stack* stack = stack_create();
	size_t current_size = 0;

	string command;
	int N;
	while (cin)
	{
		cin >> command;
		if (command == "push")
		{
			if (current_size >= size)
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

		command = "";
	}

	cout << "STACK" << endl;
	stack_print(stack);
}