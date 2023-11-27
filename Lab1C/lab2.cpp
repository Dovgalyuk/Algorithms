#include <iostream>
#include "list.h"
#include "stack.h"
#include <string>


using namespace std;

int opPriority(char op)
{
	if (op == '*')
		return 1;
	if (op == '+' || op == '-')
		return 2;
	if (op == '(')
		return 3;
}

string exprConversion(string expr)
{
	string convExpr = "";
	Stack* operationStack = stack_create();
	for (int i = 0; i < expr.length(); i++)
	{
		char tmpChar = expr[i];
		if (tmpChar == '(')
		{
			stack_push(operationStack, tmpChar);
		}
		if (tmpChar >= '0' && tmpChar <= '9')
		{
			convExpr += tmpChar;
		}
		if (tmpChar == ')')
		{
			while (stack_get(operationStack) != '(')
			{
				convExpr += stack_get(operationStack);
				stack_pop(operationStack);
			}
			stack_pop(operationStack);
		}
		if ((tmpChar =='+') || (tmpChar == '-') || (tmpChar == '*'))
		{
			while (!stack_empty(operationStack) && (opPriority(stack_get(operationStack)) <= opPriority(tmpChar)))
			{
				convExpr += stack_get(operationStack);
				stack_pop(operationStack);
			}
			stack_push(operationStack, tmpChar);
		}
	}
	while (!stack_empty(operationStack))
	{
		convExpr += stack_get(operationStack);
		stack_pop(operationStack);
	}
	stack_delete(operationStack);
	return convExpr;
}

void convToAssembler(string convExpr)
{
	for (int i = 0; i < convExpr.length(); i++)
	{
		char tmpChar = convExpr[i];
		if (tmpChar >= '0' && tmpChar <= '9')
		{
			cout << "PUSH " << tmpChar << '\n';
		}
		else
		{
			switch (tmpChar)
			{
				case '*':
				{
					cout << "POP A" << '\n';
					cout << "POP B" << '\n';
					cout << "MUL A, B" << '\n';
					cout << "PUSH A" << '\n';
					break;
				}
				case '+':
				{
					cout << "POP A" << '\n';
					cout << "POP B" << '\n';
					cout << "ADD A, B" << '\n';
					cout << "PUSH A" << '\n';
					break;
				}
				case '-':
				{
					cout << "POP A" << '\n';
					cout << "POP B" << '\n';
					cout << "SUB A, B" << '\n';
					cout << "PUSH A" << '\n';
					break;
				}
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	string expr;
	cout << "Введите выражение: ";
	cin >> expr;
	string convertedExpr = exprConversion(expr);
	convToAssembler(convertedExpr);
	return 0;
}
