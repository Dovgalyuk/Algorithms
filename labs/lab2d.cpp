#include <iostream>
#include <string>
#include "list.h"
#include "stack.h"

using namespace std;
char checkCommand(string command) {
	if (command.length() > 1)
	{
		if (command == "dup") {
			return 'p';
		}
		else if (command == "drop") {
			return 'd';
		}
		else if (command == "swap") {
			return 's';
		}
		else if (command == "over") {
			return 'o';
		}
		else if (command == "rot") {
			return 'r';
		}
		else {
			return 'e';
		}
	}
	else {
		if (command == "+" || command=="-" || command=="*" || command == "/" || command=="%")
		{
			return '+';
		}
		else if (command == ".") {
			return command[0];
		}
		else {
			if (command[0] >='0' && command[0] <= '9')
			{
				return 'n';
			}
			else {
				return 'e';
			}
		}
	}
	
}


void insertNum(Stack *stack,char num) {
	int value = atoi(&num);
	stack_push(stack, value);
}
void operationNums(Stack* stack, char operation){
	int temp1 = stack_get(stack);
	stack_pop(stack);
	int temp2 = stack_get(stack);
	stack_pop(stack);

	switch (operation)
	{
	case '+':
		stack_push(stack, temp1 + temp2);
		break;
	case '-':
		stack_push(stack, temp1 - temp2);
		break;
	case '*':
		stack_push(stack, temp1 * temp2);
		break;
	case '/':
		if (temp2 == 0)
		{
			throw "You can't devide by zero";
		}
		stack_push(stack, temp1 / temp2);
		break;
	case '%':
		if (temp2 == 0)
		{
			throw "You can't devide by zero";
		}
		stack_push(stack, temp1 % temp2);
		break;
	default:
		break;
	}
}
void swapNums(Stack* stack) {
	int temp1 = stack_get(stack);
	stack_pop(stack);
	int temp2 = stack_get(stack);
	stack_pop(stack);

	stack_push(stack, temp1);
	stack_push(stack, temp2);
}
void overNums(Stack* stack) {
	int temp1 = stack_get(stack);
	stack_pop(stack);
	int temp2 = stack_get(stack);

	stack_push(stack, temp1);
	stack_push(stack, temp2);
}
void rotNums(Stack* stack) {
	int temp1 = stack_get(stack);
	stack_pop(stack);
	int temp2 = stack_get(stack);
	stack_pop(stack);
	int temp3 = stack_get(stack);
	stack_pop(stack);

	stack_push(stack, temp2);
	stack_push(stack, temp1);
	stack_push(stack, temp3);
}

void inputCommand(Stack* stack) {
	string command;
	getline(cin, command);
	if (command == "")
	{
		cout << "Error! Enter command list\n";
		inputCommand(stack);
	}
	else
	{
		int i = 0;
		while (command[i] != '\0')
		{
			string temp = "";
			while (command[i] != 32)
			{
				if (command[i]=='\0')
				{
					break;
				}
				temp += command[i];
				i++;
			}
			switch (checkCommand(temp))
			{
			case 'n':
				insertNum(stack, temp[0]);
				break;
			case '+':
				operationNums(stack, temp[0]);
				break;
			case '.':
				cout << stack_get(stack) << "\n";
				stack_pop(stack);
				break;
			case 'p':
				stack_push(stack, stack_get(stack));
				break;
			case 'd':
				stack_pop(stack);
				break;
			case 's':
				swapNums(stack);
				break;
			case 'o':
				overNums(stack);
				break;
			case 'r':
				rotNums(stack);
				break;
			default:
				break;
			}
			if (command[i] == '\0')
			{
				break;
			}
			i++;
		}
	}
}


int main()
{
	Stack* stack = stack_create();

	inputCommand(stack);

}