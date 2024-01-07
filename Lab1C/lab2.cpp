#include <iostream>
#include "../LibraryCPP/list.h"
#include "../LibraryCPP/stack.h"
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

return 0;
}

string exprConversion(string expr)
{
	string convExpr = "";
	Stack* operationStack = stack_create();
	for (long unsigned int i = 0; i < expr.length(); i++)
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


int main()
{
	setlocale(LC_ALL, "Russian");
	string expr;
	cout << "Введите выражение: ";
	cin >> expr;
	string convertedExpr = exprConversion(expr);
	cout << convertedExpr;
	return 0;
}