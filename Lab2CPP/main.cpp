#include <fstream>
#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

int priority(char op)
{
    if (op == '*')
        return 2;

    if (op == '+' || op == '-')
        return 1;

    return 0;
}

void print_operation(char op)
{
    cout << "POP A" << endl;
    cout << "POP B" << endl;

    if (op == '+')
    {
        cout << "ADD A, B" << endl;
        cout << "PUSH A" << endl;
    }
    else if (op == '-')
    {
        cout << "SUB B, A" << endl;
        cout << "PUSH B" << endl;
    }
    else if (op == '*')
    {
        cout << "MUL A, B" << endl;
        cout << "PUSH A" << endl;
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cerr << "Usage: ExpressionToAsm <input file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);

    if (!input.is_open())
    {
        cerr << "Cannot open input file" << endl;
        return 1;
    }

    string expression;
    getline(input, expression);

    Stack *ops = stack_create();
    int length = (int)expression.size();

    for (int i = 0 ; i < length ; ++i)
    {
        char c = expression[i];

        if (c == ' ')
            continue;

        if (c >= '0' && c <= '9')
        {
            int number = 0;

            while (i < length && expression[i] >= '0' && expression[i] <= '9')
            {
                number = number * 10 + (expression[i] - '0');
                ++i;
            }

            --i;
            cout << "PUSH " << number << endl;
        }
        else if (c == '(')
        {
            stack_push(ops, (Data)c);
        }
        else if (c == ')')
        {
            while (!stack_empty(ops) && (char)stack_get(ops) != '(')
            {
                char op = (char)stack_get(ops);
                stack_pop(ops);
                print_operation(op);
            }

            if (!stack_empty(ops))
                stack_pop(ops);
        }
        else if (c == '+' || c == '-' || c == '*')
        {
            while (!stack_empty(ops))
            {
                char top = (char)stack_get(ops);

                if (top == '(' || priority(top) < priority(c))
                    break;

                stack_pop(ops);
                print_operation(top);
            }

            stack_push(ops, (Data)c);
        }
    }

    while (!stack_empty(ops))
    {
        char op = (char)stack_get(ops);
        stack_pop(ops);
        print_operation(op);
    }

    stack_delete(ops);
    return 0;
}
