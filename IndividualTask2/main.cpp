#include <iostream>
#include <string>
#include "stack.h"

void function(Stack* num1, Stack* num2) {
	stack_push(num1, stack_get(num2));
	stack_pop(num2);
}

int main() {
	Stack* marks = stack_create();
	Stack* polish = stack_create();
	std::string expression;
	int num1, num2;
	std::cin >> expression;

	//Reverse Polish notation

	for (int i = 0; i < expression.size(); i++) {
		if (isdigit(expression[i])) {
			stack_push(polish, expression[i]);
		}
		else {
			while (true) {
				// Ya ne znau kak ymenshit` eto yslovie
				if ((expression[i] == '+' || expression[i] == '-') && (stack_get(marks) == '*' || stack_get(marks) == '/')) {
					function(polish, marks);
				}
				else if (expression[i] == stack_get(marks)) {
					function(polish, marks);
					stack_push(marks, expression[i]);
					break;
				}
				// Ya ne znau kak ymenshit` eto yslovie
				else if ((expression[i] == '-' && stack_get(marks) == '+') || (expression[i] == '+' && stack_get(marks) == '-')) {
					function(polish, marks);
					stack_push(marks, expression[i]);
					break;
				}
				else {
					stack_push(marks, expression[i]);
					break;
				}
			}
		}
	}
	while (!stack_empty(marks)) {
		function(polish, marks);
	}
	while (!stack_empty(polish)) {
		function(marks, polish);
	}

	//Calculator PRN

	for (int i = 0; i < expression.size(); i++) {
		if (isdigit(stack_get(marks))) {
			stack_push(polish, stack_get(marks));
			stack_pop(marks);
		}
		else {
			num2 = stack_get(polish)-48;
			stack_pop(polish);
			num1 = stack_get(polish)-48;
			stack_pop(polish);

			switch (stack_get(marks)) {
			case '*': {
				num1 *= num2;
				stack_push(polish, num1+48);
				stack_pop(marks);
			}break;
			case '/': {
				num1 /= num2;
				stack_push(polish, num1+48);
				stack_pop(marks);
			}break;
			case '+': {
				num1 += num2;
				stack_push(polish, num1+48);
				stack_pop(marks);
			}break;
			case '-': {
				num1 -= num2;
				stack_push(polish, num1+48);
				stack_pop(marks);
			}break;
			}
		}
	}

	std::cout << "Result: " << stack_get(polish)-48 << std::endl;

	system("pause");
	stack_delete(marks);
	stack_delete(polish);
}
