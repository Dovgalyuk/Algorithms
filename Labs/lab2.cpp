#include <iostream>
#include <string>
#include "stack.h"

void plus(Stack* stack) {
	int v1 = stack_get(stack); stack_pop(stack);
	int v2 = stack_get(stack); stack_pop(stack);
	stack_push(stack,v1 + v2);
}

void minus(Stack* stack) {
	int v1 = stack_get(stack); stack_pop(stack);
	int v2 = stack_get(stack); stack_pop(stack);
	stack_push(stack,v1 - v2);
}

void multiply(Stack* stack) {
	int v1 = stack_get(stack); stack_pop(stack);
	int v2 = stack_get(stack); stack_pop(stack);
	stack_push(stack, v1 * v2);
}

void divide(Stack* stack) {
	int v1 = stack_get(stack); stack_pop(stack);
	int v2 = stack_get(stack); stack_pop(stack);
	stack_push(stack,v1 / v2);
}

void percent(Stack* stack) {
	int v1 = stack_get(stack); stack_pop(stack);
	int v2 = stack_get(stack); stack_pop(stack);
	stack_push(stack, v1 / v2 * 100);
}

void inverse(Stack* stack) {
	int value = stack_get(stack); stack_pop(stack);
	stack_push(stack, value == 0);
}

void compare(Stack* stack) {
	int v1 = stack_get(stack); stack_pop(stack);
	int v2 = stack_get(stack); stack_pop(stack);
	stack_push(stack, v1 > v2);
}

void duplicate(Stack* stack) {
	stack_push(stack, stack_get(stack));
}

void print(Stack* stack) {
	std::cout << stack_get(stack) << std::endl; 
	stack_pop(stack);
}

void get_number(Stack* stack) {
	int value;
	std::cin >> value;
	if (1 <= value && value <= 9)
		stack_push(stack, value);
	else
		throw std::invalid_argument("1-9 values were expected");
}

void execute(Stack* stack, const std::string input) {
	for (char ch : input) {
		if ('1' <= ch && ch <= '9') {
			stack_push(stack, ch - '0');
			continue;
		}
		switch (ch) {
		case '+':
			plus(stack);
			break;
		case '-':
			minus(stack);
			break;
		case '*':
			multiply(stack);
			break;
		case '/':
			divide(stack);
			break;
		case '%':
			percent(stack);
			break;
		case '!':
			inverse(stack);
			break;
		case '`':
			compare(stack);
			break;
		case ':':
			duplicate(stack);
			break;
		case '.':
			print(stack);
			break;
		case '&':
			get_number(stack);
			break;
		default:
			throw std::invalid_argument("Unexpected operand : " + ch);
		}
	}
}


int main() {
	
	Stack* stack = stack_create();
	
	std::string input;
	std::getline(std::cin, input);

	try {
		execute(stack, input);
	}
	catch (std::invalid_argument& e) {
		std::cout << e.what();
	}
	stack_delete(stack);
}
