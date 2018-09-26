#include <iostream>
#include "stack.h"

using namespace std;

void CalcFun(int &ch1, int &ch2, Stack *znak, Stack *stack, int t)
{
	stack_pop(znak);
	ch1 = stack_get(stack);
	stack_pop(stack);
	ch2 = stack_get(stack);
	stack_pop(stack);
	if	(t == '+')
		stack_push(stack, ch1 + ch2);
	else if (t == '-') //-
		stack_push(stack, ch2 - ch1);
	else if (t == '*') //*
		stack_push(stack, ch1 * ch2);
	else if (t == '/') // /
		stack_push(stack, ch2 / ch1);
}

int POW(int var, int power)
{
	int otv = 1;
	for (int i = 0; i < power; i++)
		otv *= var;
	return otv;
}


int GetPriority(int i)
{
	if(i == '+' || i == '-')
		return 1;
	else if(i == '*' || i == '/')
		return 2;
	else
		exit(0);

}

void CheckStack(char c, Stack *znak, Stack *stack)
{
	int i = static_cast<int>(c);
	int p1, p2, ch1, ch2, t;

	if(stack_empty(znak))
	{
		stack_push(znak, i);
		return;
	}

	p1 = GetPriority(i);
	t = stack_get(znak);
	p2 = GetPriority(t);

	if(p2<p1)
	{
		stack_push(znak, i);
		return;
	}
	else
	{
		while(p2>=p1)
		{
			
			CalcFun(ch1, ch2, znak, stack, t);

			if(!stack_empty(znak))
			{
				t = stack_get(znak);
				p2 = GetPriority(t);
			}
			else
			{
				stack_push(znak, i);
				return;
			}
		}
		stack_push(znak, i);
	}
}

void CountNumber(int *t_last, int tmp[], Stack *stack)
{
	int var=0;
	for(int i=(*t_last); i>0; i--)
	{	
		var += tmp[(*t_last) - i] * POW(10,i-1);
	}
	(*t_last) = 0;
	stack_push(stack, var);
}


int main()
{
	Stack *stack = stack_create();
	Stack *znak = stack_create();
	char c;
	int tmp[10];
	int t_last=0;
	c = cin.get();
	while(c != '\n')
	{
		if(c == '+' || c == '-' || c == '*' || c == '/')
		{
			CountNumber(&t_last,tmp,stack);
			CheckStack(c, znak, stack);
		}
		else
		{
			tmp[t_last] = c - '0';
			t_last++;
		}
		c = cin.get();
	}
	CountNumber(&t_last,tmp,stack);

	int t=0, ch1, ch2;
	while(!stack_empty(znak))
	{
		t = stack_get(znak);
		CalcFun(ch1, ch2, znak, stack, t);
	}

	cout<< stack_get(stack) << endl;
	stack_pop(stack);
	stack_delete(stack);
	stack_delete(znak);
	return 0;
}
