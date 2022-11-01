#include <iostream>
#include "stack.h"
#include "list.h"
#include <cctype>
#include <string>

using namespace std;

int priority(const char& ch)
{
    switch (ch)
    {
    case '(':
        return 0;
    case ')':
        return 1;
    case '+':
    case '-':
        return 3;
        break;
    case '*':
        return 4;
        break;
    }
}

Stack *muladdsub(Stack *stack)
{
    cout << "POP A\n";
    switch (stack_get(stack))
    {
        case '*':
            stack_pop(stack);
            cout << "POP B\nMUL A, B\n";
            break;
        case '+':
            stack_pop(stack);
            cout << "POP B\nADD A, B\n";
            break;
        case '-':
            stack_pop(stack);
            cout << "POP B\nSUB A, B\n";
            break;
        default:
            break;
    }
    cout << "PUSH A\n";
    return stack;
}

void third(string str)
{
    Stack* stack = stack_create();
    int a;
    for (int i = 0; i < str.length();i++)
    {
        if (str[i] != '(' && str[i] != ')')
        {
            if (stack_empty(stack) && !isdigit(str[i]))
                stack_push(stack, str[i]);
            else if (isdigit(str[i]))
                cout << "PUSH " << str[i] << "\n";
            else if (priority(str[i]) >= priority(stack_get(stack)))
                stack_push(stack, str[i]);
            else
            {
                while (!stack_empty(stack))
                {
                    muladdsub(stack);
                }
                stack_push(stack, str[i]);
            }
        }
        else
        {
            if (str[i] == ')')
            {
                while (stack_get(stack) != '(')
                {
                    muladdsub(stack);
                }
                stack_pop(stack);
            }
            else
            {
                stack_push(stack, str[i]);
            }
        }
    }
    while (!stack_empty(stack))
    {
        muladdsub(stack);
    }
    stack_delete(stack);
}

int main()
{
    string str;
    cout << "Enter string :\n";
    cin >> str;
    third(str);
}
