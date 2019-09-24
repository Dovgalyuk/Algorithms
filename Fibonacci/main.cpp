#include <iostream>
#include "stack.h"

int main() {
	int n;
	std::cin >> n;
	
	int buffSize = n / 2 + n % 2;

	int* depth = new int[buffSize];
	int* buff = new int[buffSize];
	for (int i = 0; i < buffSize; i++) {
		buff[i] = 0;
		depth[i] = 0;
	}

	Stack* stack = stack_create();

	int d = 0;
	stack_push(stack, n);
	depth[0] = 1;
	bool l = true;

	do {
		int curr = stack_get(stack);
		stack_pop(stack);
		if (curr <= 1) {
			if (l) {
				l = false;
			}
			buff[d]++;
			depth[d]--;
		} else if (l) {
			d++;
			depth[d] = 0;
			buff[d] = 0;
			for (int i = curr; i > 0; i--) {
				stack_push(stack, i);
				depth[d]++;
			}
			l = false;
		}
		else {
			stack_push(stack, curr - 2);
			l = true;
		}

		if (depth[d] == 1) {
			buff[d - 1] += buff[d];
			d--;
		}

	} while (d > 0);

	std::cout << buff[0];
	stack_delete(stack);
}