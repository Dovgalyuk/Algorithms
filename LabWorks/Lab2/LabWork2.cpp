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
}

string exprConversion(string expr)
{
	string convExpr = "";
	if (expr.find("(")!=string::npos)
	{
		int count = expr.find(")") - expr.find("(") + 1;
		string x = expr.substr(expr.find("(") + 1, count - 2);
		convExpr += exprConversion(x);
		expr.replace(expr.find("("), count, "");
	}
	Stack* operationStack = stack_create();
	for (int i = 0; i < expr.length(); i++)
	{
		char tmpChar = expr[i];
		if (tmpChar >= '0' && tmpChar <= '9')
		{
			convExpr += tmpChar;
		}
		if ((tmpChar =='+') || (tmpChar == '-') || (tmpChar == '*'))
		{
			if ((!stack_empty(operationStack))&&(opPriority(stack_get(operationStack)) <= opPriority(tmpChar)))
			{
				while (!stack_empty(operationStack))
				{
					convExpr += stack_get(operationStack);
					stack_pop(operationStack);

				}
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
	Stack* dataStack = stack_create();
	for (int i = 0; i < convExpr.length(); i++)
	{
		char tmpChar = convExpr[i];
		if (tmpChar >= '0' && tmpChar <= '9')
		{
			stack_push(dataStack, tmpChar);
			cout << "PUSH " << tmpChar << '\n';
		}
		else
		{
			switch (tmpChar)
			{
				case '*':
				{
					int A = stack_get(dataStack);
					int B = stack_get(dataStack);
					stack_pop(dataStack);
					cout << "POP A" << '\n';
					stack_pop(dataStack);
					cout << "POP B" << '\n';
					cout << "MUL A, B" << '\n';
					stack_push(dataStack, A * B);
					cout << "PUSH A" << '\n';
					break;
				}
				case '+':
				{
					int A = stack_get(dataStack);
					int B = stack_get(dataStack);
					stack_pop(dataStack);
					cout << "POP A" << '\n';
					stack_pop(dataStack);
					cout << "POP B" << '\n';
					stack_push(dataStack, A + B);
					cout << "ADD A, B" << '\n';
					cout << "PUSH A" << '\n';
					break;
				}
				case '-':
				{
					int A = stack_get(dataStack);
					int B = stack_get(dataStack);
					stack_pop(dataStack);
					cout << "POP A" << '\n';
					stack_pop(dataStack);
					cout << "POP B" << '\n';
					stack_push(dataStack, A - B);
					cout << "SUB A, B" << '\n';
					cout << "PUSH A" << '\n';
					break;
				}

			}
		}
	}
	stack_delete(dataStack);
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