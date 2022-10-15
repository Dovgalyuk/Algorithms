#include <iostream>
#include "stack.h"
#include "list.h"
#include <cctype>

using namespace std;

void third(string& str)
{
    Stack* stack = stack_create();

    for (char ch : str)
    {
        if (isdigit(ch))
            stack_push(stack, int(ch) - int('0'));
        else
            stack_push(stack, ch);
    }
    Stack* buf = stack_create();
    int a, b;
    while (!stack_empty(stack))
    {
        stack_push(buf, stack_get(stack));
        stack_pop(stack);
    }
    while (!stack_empty(buf))
    {
        if(stack_get(buf)==')')
        {
            b = stack_get(stack);
            cout << "POP A\n";
            stack_pop(stack);
            stack_pop(buf);
            switch (stack_get(stack))
            {
            case '*':
                stack_pop(stack);
                a = stack_get(stack);
                cout << "POP B\n";
                stack_pop(stack);
                cout << "MUL A, B\n";
                a = a * b;
                stack_pop(stack);
                break;
            case '-':
                stack_pop(stack);
                a = stack_get(stack);
                cout << "POP B\n";
                stack_pop(stack);
                cout << "SUB A, B\n";
                a = a - b;
                stack_pop(stack);
                break;
            case '+':
                stack_pop(stack);
                a = stack_get(stack);
                cout << "POP B\n";
                stack_pop(stack);
                cout << "ADD A, B\n";
                a = a + b;
                stack_pop(stack);
                break;
            default:
                break;
            }
            stack_push(stack, a);
            cout << "PUSH A\n";
        }
        if (!stack_empty(buf))
        {
            stack_push(stack, stack_get(buf));
            if (stack_get(buf) <= 9 && stack_get(buf) >= 1)
                cout << "PUSH " << stack_get(buf) << "\n";
            stack_pop(buf);
        }
    }
    while (!stack_empty(stack))
    {
        if (stack_get(stack) == '*')
        {
            stack_pop(stack);
            b = stack_get(buf);
            cout << "POP A\n";
            stack_pop(buf);
            a = stack_get(stack);
            cout << "POP B\n";
            stack_pop(stack);
            cout << "MUL A, B\n";
            a = a * b;
            stack_push(stack, a);
            cout << "PUSH A\n";
        }
        if(!stack_empty(stack))
        {
            stack_push(buf, stack_get(stack));
            stack_pop(stack);
        }
    }
    a = stack_get(buf);
    stack_pop(buf);
    if (!stack_empty(buf))
    {
        stack_push(buf, a);
        while (!stack_empty(buf))
        {
            if (stack_empty(stack))
            {
                a = stack_get(buf);
                cout << "POP A\n";
                stack_pop(buf);
            }
            else
            {
                a = stack_get(stack);
                cout << "POP A\n";
                stack_pop(stack);
            }
            switch (stack_get(buf))
            {
            case'+':
                stack_pop(buf);
                b = stack_get(buf);
                cout << "POP B\n";
                a = a + b;
                cout << "ADD A,B\n";
                stack_push(stack, a);
                cout << "PUSH A\n";
                break;
            case'-':
                stack_pop(buf);
                b = stack_get(buf);
                cout << "POP B\n";
                a = a - b;
                cout << "SUB A,B\n";
                stack_push(stack, a);
                cout << "PUSH A\n";
                break;
            default:

                break;
            }
            if (!stack_empty(buf))
            {
                stack_push(stack, stack_get(buf));
                stack_pop(buf);
            }
        }
    }
    stack_delete(stack);
    stack_delete(buf);
}

int main()
{
    string str;
    cout << "Enter string :\n";
    cin >> str;
    third(str);
}
