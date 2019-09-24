#include <iostream>
#include "stack.h"

int main() {
	int n;
	std::cin >> n;


	Stack* stack = stack_create();
	Stack* otherStack = stack_create();

	int d = 0;
	int result = 0;
	stack_push(stack, n);
	stack_push(otherStack, 1);
	bool l = true;

	do {
		int curr = stack_get(stack);
		stack_pop(stack);
		if (curr <= 1) {
			if (l) {
				l = false;
			}
			result++;
			int tmp = stack_get(otherStack);
			stack_pop(otherStack);
			stack_push(otherStack, tmp - 1);
		} else if (l) {
			d++;
			stack_push(otherStack, 0);
			for (int i = curr; i > 0; i--) {
				stack_push(stack, i);
				int tmp = stack_get(otherStack);
				stack_pop(otherStack);
				stack_push(otherStack, tmp + 1);
			}
			l = false;
		}
		else {
			stack_push(stack, curr - 2);
			l = true;
		}

		if (stack_get(otherStack) == 1) {
			stack_pop(otherStack);
			d--;
		}

	} while (d > 0);

	std::cout << result;
	stack_delete(stack);
}