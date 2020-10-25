#include <iostream>
#include <string>
#include "stack.h"

//Reverse Polish notation

int main() {
	Stack* marks = stack_create();
	std::string polish, expression;
	std::string newmarks;
	int num1, num2;
	std::cin >> expression;

	for (int i = 0; i < expression.size(); i++) {
		if (isdigit(expression[i])) {
			polish += expression[i];
		}
		else {
			if ((expression[i] == '*' || expression[i] == '/') && (stack_get(marks) == '+' || stack_get(marks) == '-')) {
				stack_push(marks, expression[i]);
			}
			else if ((expression[i] == '+' || expression[i] == '-') && (stack_get(marks) == '*' || stack_get(marks) == '/')) {
				while (true) {
					if ((expression[i] == '+' || expression[i] == '-') && (stack_get(marks) == '*' || stack_get(marks) == '/')) {
						newmarks = stack_get(marks);
						stack_pop(marks);
						polish += newmarks;
					}
					else if ((expression[i] == '+' || expression[i] == '-') && (stack_get(marks) == '+' || stack_get(marks) == '-')) {
						newmarks = stack_get(marks);
						stack_pop(marks);
						polish += newmarks;
						stack_push(marks, expression[i]);
						break;
					}
					else {
						stack_push(marks, expression[i]);
						break;
					}
				}	
			}
			else if ((expression[i] == '*' || expression[i] == '/') && (stack_get(marks) == '*' || stack_get(marks) == '/')) {
				newmarks = stack_get(marks);
				stack_pop(marks);
				polish += newmarks;
				stack_push(marks, expression[i]);
			}
			else if ((expression[i] == '+' || expression[i] == '-') && (stack_get(marks) == '+' || stack_get(marks) == '-')) {
				newmarks = stack_get(marks);
				stack_pop(marks);
				polish += newmarks;
				stack_push(marks, expression[i]);
			}
			else {
				stack_push(marks, expression[i]);
			}
		}
	}
	while (!stack_empty(marks)) {
		newmarks = stack_get(marks);
		stack_pop(marks);
		polish += newmarks;
	}


	//Calculator PRN

	for (int i = 0; i < polish.size(); i++) {
		if (isdigit(polish[i])) {
			stack_push(marks, polish[i] - 48);
		}
		else {
			num2 = stack_get(marks);
			stack_pop(marks);
			num1 = stack_get(marks);
			stack_pop(marks);

			switch (polish[i]) {
				case '*': {
					num1 *= num2;
					stack_push(marks, num1);
				}break;
				case '/': {
					num1 /= num2;
					stack_push(marks, num1);
				}break;
				case '+': {
					num1 += num2;
					stack_push(marks, num1);
				}break;
				case '-': {
					num1 -= num2;
					stack_push(marks, num1);
				}break;
			}
		}
	}
	std::cout <<"Reverse Polish notation: "<< polish << std::endl;
	std::cout <<"Result: "<< stack_get(marks) << std::endl;

	system("pause");
	stack_delete(marks);
}

