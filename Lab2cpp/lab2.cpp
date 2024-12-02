#include <iostream>
#include <fstream>
#include <cctype>
#include "stack.h"
using namespace std;

// Helper function to perform arithmetic operations
int performOperation(char operation, int operand1, int operand2)
{
    switch (operation)
    {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/':
            if (operand2 == 0)
                throw runtime_error("Division by zero");
            return operand1 / operand2;
        default: throw invalid_argument("Invalid operation");
    }
}

// Determines precedence of operators
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

int evaluateExpression(const string &expression)
{
    Stack *operands = stack_create(); // Stack for numbers
    Stack *operators = stack_create(); // Stack for operators

    for (size_t i = 0; i < expression.length(); ++i)
    {
        char token = expression[i];

        if (isspace(token))
        {
            continue; // Skip whitespace
        }

        if (isdigit(token))
        {
            int number = 0;
            while (i < expression.length() && isdigit(expression[i]))
            {
                number = number * 10 + (expression[i] - '0');
                ++i;
            }
            --i; // Adjust for loop increment
            stack_push(operands, number);
        }
        else if (token == '(')
        {
            stack_push(operators, token);
        }
        else if (token == ')')
        {
            while (!stack_empty(operators) && stack_get(operators) != '(')
            {
                int operand2 = stack_get(operands);
                stack_pop(operands);
                int operand1 = stack_get(operands);
                stack_pop(operands);
                char op = stack_get(operators);
                stack_pop(operators);
                stack_push(operands, performOperation(op, operand1, operand2));
            }
            stack_pop(operators); // Pop '('
        }
        else
        {
            while (!stack_empty(operators) && precedence(stack_get(operators)) >= precedence(token))
            {
                int operand2 = stack_get(operands);
                stack_pop(operands);
                int operand1 = stack_get(operands);
                stack_pop(operands);
                char op = stack_get(operators);
                stack_pop(operators);
                stack_push(operands, performOperation(op, operand1, operand2));
            }
            stack_push(operators, token);
        }
    }

    while (!stack_empty(operators))
    {
        int operand2 = stack_get(operands);
        stack_pop(operands);
        int operand1 = stack_get(operands);
        stack_pop(operands);
        char op = stack_get(operators);
        stack_pop(operators);
        stack_push(operands, performOperation(op, operand1, operand2));
    }

    int result = stack_get(operands);
    stack_pop(operands);

    stack_delete(operands);
    stack_delete(operators);

    return result;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open())
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string expression;
    getline(input, expression);

    try
    {
        int result = evaluateExpression(expression);
        cout << result << endl;
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    input.close();
    return 0;
}
