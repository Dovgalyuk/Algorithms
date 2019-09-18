#include <iostream>
#include "stack.h"

int main() {
	int n;
	std::cin >> n;
	Stack* stack = stack_create();
	stack_push(stack, 1);
	stack_push(stack, 1);
	for (int i = 2; i < n; i++) {
		int curr = stack_get(stack);
		stack_pop(stack);
		int prev = stack_get(stack);
		stack_push(stack, curr);
		stack_push(stack, curr + prev);
	}
	std::cout << stack_get(stack);
}