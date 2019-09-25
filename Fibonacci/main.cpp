#include <iostream>
#include "stack.h"

int main() {
	int n;
	std::cin >> n;

	Stack* stack = stack_create();
	Stack* depthStack = stack_create();
	Stack* resultStack = stack_create();

	stack_push(stack, n);
	stack_push(depthStack, 1);

	do {
		int curr = stack_get(stack);
		int currDepth = stack_get(depthStack);
		stack_pop(stack);
		stack_pop(depthStack);

		if (curr <= 1) {
			stack_push(resultStack, 1);
		}
		else {
			if (currDepth == 1) {
				stack_push(stack, curr);
				stack_push(depthStack, 2);
				for (int i = curr - 1; i > 0; i--) {
					stack_push(stack, i);
					stack_push(depthStack, 1);
				}
			}
			else if (currDepth == 2) {
				stack_push(stack, curr);
				stack_push(depthStack, 3);
				stack_push(stack, curr - 2);
				stack_push(depthStack, 1);
			}
		}

		if (currDepth == 3) {
			int tmp = stack_get(resultStack);
			stack_pop(resultStack);
			tmp += stack_get(resultStack);
			stack_pop(resultStack);
			stack_push(resultStack, tmp);
		}
	} while (!stack_empty(depthStack));

	std::cout << stack_get(resultStack);
	stack_delete(stack);
}