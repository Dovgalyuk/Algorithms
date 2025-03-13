#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

using namespace std;

int precedence(char op)
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int applyOp(int a, int b, char op)
{
    switch (op) 
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

int evaluate(const string& expression)
{
    Stack* values = stack_create(); 
    Stack* ops = stack_create(); 

    for (size_t i = 0; i < expression.length(); i++)
    {
        if (isdigit(expression[i])) 
        {
            int val = 0;
            while (i < expression.length() && isdigit(expression[i]))
            {
                val = (val * 10) + (expression[i] - '0');
                i++;
            }
            stack_push(values, val);
            i--;
        }
        else if (expression[i] == '(')
        {
            stack_push(ops, (Data)expression[i]);
        }
        else if (expression[i] == ')') 
        {
            while (!stack_empty(ops) && stack_get(ops) != (Data)'(')
            {
                int val2 = stack_get(values);
                stack_pop(values);
                int val1 = stack_get(values);
                stack_pop(values);
                char op = (char)stack_get(ops);
                stack_pop(ops);
                stack_push(values, applyOp(val1, val2, op));
            }
            stack_pop(ops); 
        }
        else if (expression[i] == '+' || expression[i] == '-' || 
            expression[i] == '*' || expression[i] == '/') 
        {
            while (!stack_empty(ops) && precedence((char)stack_get(ops)) >= precedence(expression[i]))
            {
                int val2 = stack_get(values);
                stack_pop(values);
                int val1 = stack_get(values);
                stack_pop(values);
                char op = (char)stack_get(ops);
                stack_pop(ops);
                stack_push(values, applyOp(val1, val2, op));
            }
            stack_push(ops, (Data)expression[i]);
        }
    }

    while (!stack_empty(ops))
    {
        int val2 = stack_get(values);
        stack_pop(values);
        int val1 = stack_get(values);
        stack_pop(values);
        char op = (char)stack_get(ops);
        stack_pop(ops);
        stack_push(values, applyOp(val1, val2, op));
    }

    int result = stack_get(values);
    stack_delete(values);
    stack_delete(ops);
    return result;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    istream* input = &cin;
    ifstream inputFile;

    if (argc >= 2)
    {
        inputFile.open(argv[1]);
        if (!inputFile)
        {
            cerr << "Ошибка: не удалось открыть файл " << argv[1] << endl;
            return 1;
        }
        input = &inputFile;
    }

    string expression;

    while (getline(*input, expression))
    {
        cout << evaluate(expression) << endl;
    }

    return 0;
}
