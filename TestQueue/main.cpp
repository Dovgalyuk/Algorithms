//Попов Владимир 8091
#include <iostream>
#include "stack.h"

int charToInt(char c) {
	switch (c)
	{
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	default: return 10;
	}
}

int main()
{
	int sum=0;
	Stack *st, *f1;
	st = stack_create();
	f1 = stack_create();
	int i=0;
	char exp[100];
	std::cin >> exp;
	int len = strlen(exp);
	int s = 0;
	int dec = 1;
	stack_push(f1, '\0');
	char g, e;

	while (s <= len) {

		g = stack_get(f1);
		e = exp[s];

		if ((s==len) && (g == '\0')) break;

		else if ((((s == len) || ((e == '+') || (e == '-'))) && (g != '\0')) || (((e == '*')||(e=='/')) && ((g == '*')||(g=='/'))))
		{
			stack_push(st, stack_get(f1)); stack_pop(f1);
		}
		else if ((((e == '+') || (e == '-')) && (g == '\0')) || (((e == '*')||(e=='/')) && ((g!='*')&&(g!='/'))))
		{
			stack_push(f1, exp[s]); s++;
		}
		else {
			stack_push(st, exp[s]); s++;
		}
	}
	char c;
	while (!stack_empty(st))
	{
		stack_push(f1, stack_get(st));
		stack_pop(st);
	}
	while (!stack_empty(f1))
	{
		c = stack_get(f1);
		if (c == '\0') break;
		if (c == '+')
		{
			int a = stack_get(st);
			stack_pop(st);
			a = a + stack_get(st);
			stack_pop(st);
			stack_push(st, a);
			stack_pop(f1);
			c = stack_get(f1);
		}
		else if (c == '-')
		{
			int a = stack_get(st);
			stack_pop(st);
			int b = stack_get(st);
			stack_pop(st);
			stack_push(st, b-a);
			stack_pop(f1);
			c = stack_get(f1);
		}
		else if (c == '*')
		{
			int a = stack_get(st);
			stack_pop(st);
			a = a * stack_get(st);
			stack_pop(st);
			stack_push(st, a);
			stack_pop(f1);
			c = stack_get(f1);
		}
		else if (c == '/')
		{
			int a = stack_get(st);
			stack_pop(st);
			int b = stack_get(st);
			stack_pop(st);
			stack_push(st, b / a);
			stack_pop(f1);
			c = stack_get(f1);
		}
		else {
			stack_push(st, charToInt(c));
			stack_pop(f1);
			c = stack_get(f1);
		}
	}

	std::cout << stack_get(st);
	stack_delete(st);
	stack_delete(f1);
}
