#include <iostream>
#include "stack.h"

int fun(char a);

int main()
{
	char a[100];
	std::cin >> a;
	Stack* f;
	f = stack_create();
	int dl_str = strlen(a);
	for (dl_str--; dl_str >= 0; dl_str--) {
		stack_push(f, a[dl_str]);
		std::cout << (char)stack_get(f);
	}
	Stack* g;
	g = stack_create();
	int i;
	int j;
	while (!stack_empty(f)) {
		i = fun(stack_get(f));
		if (i != -1) {
			stack_push(g, i);
		}
		else {
			if (!stack_empty(g)) {
				i = stack_get(g);
				stack_pop(g);
			}
			else {
				std::cout << "UNDERFLOW";
				return 0;
			}

			if (!stack_empty(g)) {
				j = stack_get(g);
				stack_pop(g);
			}
			else {
				std::cout << "UNDERFLOW";
				return 0;
			}

			switch (stack_get(f))
			{
			case '+': {stack_push(g, i + j); break; }
			case '-': {stack_push(g, j - i); break; }
			case '*': {stack_push(g, i * j); break; }
			case '/': {if (i == 0) {
				std::cout << "ZERO";
				return 0;
			}
					stack_push(g, j / i); break; }
			default:
				break;
			}
		}
		stack_pop(f);
	}
	int y = 0;
	while (!stack_empty(g)) {
		y++;
		stack_pop(g);
	}
	if (y > 1) {
		std::cout << "OVERFLOW";
		return 0;
	}
	return 0;
}

int fun(char a) {
	switch (a)
	{
	case '0': {return 0; break;}
	case '1': {return 1; break; }
	case '2': {return 2; break; }
	case '3': {return 3; break; }
	case '4': {return 4; break; }
	case '5': {return 5; break; }
	case '6': {return 6; break; }
	case '7': {return 7; break; }
	case '8': {return 8; break; }
	case '9': {return 9; break; }
	default:
		return -1;
		break;
	}
}
