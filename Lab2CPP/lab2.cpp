#include <iostream>
#include <string>
#include <fstream>
#include "stack.h"

using namespace std;

void task1(string line, int* reg, Stack* stack)
{

	string command = line, argument = line.erase(0, line.find(' ') + 1);
	command.erase(command.find(' '));
	if (command == "POP")
	{
		if (stack_empty(stack))
		{
			cout << "Error: stack is empty" << endl;
			return;
		}
		reg[argument[0] - 'A'] = stack_get(stack);
		stack_pop(stack);
	}
	else if (command == "PUSH")
	{
		if (isdigit(argument[0]))
			stack_push(stack, stoi(argument));
		else
			stack_push(stack, reg[argument[0] - 'A']);
	}
	else
	{
		cout << "Error: unknown command" << endl;
	}
}

int main()
{
	int registers[] = { 0, 0, 0, 0 };
	Stack* stack = stack_create();

	ifstream fin;
	fin.open("input.txt");

	string line;
	while (getline(fin, line))
		task1(line, registers, stack);

	fin.close();
	stack_delete(stack);

	for (size_t i = 0; i < 4; i++)
		cout << (char) ('A' + i) << " - " << registers[i] << endl;
}
