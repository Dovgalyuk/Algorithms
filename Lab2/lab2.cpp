#include <iostream>
#include "stack.h"
#include "list.h"
#include <cctype>
#include <string>

using namespace std;

void third(string& str)
{
    Stack* stack = stack_create();
    for (int i = str.length(); i >= 0;i--)
    {
        if (isdigit(str[i]))
            stack_push(stack, int(str[i]) - int('0'));
        else
            stack_push(stack, str[i]);
    }
    Stack* buf = stack_create();
    int a;
    while (!stack_empty(stack))
    {
        if(stack_get(stack)==')')
        {
            a = stack_get(buf);
            cout << "POP A\n";
            stack_pop(stack);
            stack_pop(buf);
            switch (stack_get(buf))
            {
            case '*': 
                stack_pop(buf);
                cout << "POP B\n";
                stack_pop(buf);
                cout << "MUL A, B\n";
                stack_pop(buf);
                break;
            case '-':
                stack_pop(buf);
                cout << "POP B\n";
                stack_pop(buf);
                cout << "SUB A, B\n";
                stack_pop(buf);
                break;
            case '+':
                stack_pop(buf);
                cout << "POP B\n";
                stack_pop(buf);
                cout << "ADD A, B\n";
                stack_pop(buf);
                break;
            default:
                break;
            }
            stack_push(buf, a);
            cout << "PUSH A\n";
        }
        if (!stack_empty(stack))
        {
            stack_push(buf, stack_get(stack));
            if (stack_get(stack) <= 9 && stack_get(stack) >= 1)
                cout << "PUSH " << stack_get(stack) << "\n";
            stack_pop(stack);
        }
    }
    while (!stack_empty(buf))
    {
        if (stack_get(buf) == '*')
        {
            stack_pop(buf);
            cout << "POP A\n";
            a = stack_get(buf);
            stack_pop(buf);
            cout << "POP B\n";
            stack_pop(stack);
            cout << "MUL A, B\n";
            stack_push(buf, a);
            cout << "PUSH A\n";
        }
        if(!stack_empty(buf))
        {
            stack_push(stack, stack_get(buf));
            stack_pop(buf);
        }
    }
    a = stack_get(stack);
    stack_pop(stack);
    if(!stack_get(stack)==0)
    {
        stack_push(stack, a);
        while (!stack_empty(stack))
        {
            if (stack_empty(buf))
            {
                a = stack_get(stack);
                cout << "POP A\n";
                stack_pop(stack);
            }
            else
            {
                a = stack_get(buf);
                cout << "POP A\n";
                stack_pop(buf);
            }
            switch (stack_get(stack))
            {
            case'+':
                stack_pop(stack);
                cout << "POP B\n";
                cout << "ADD A,B\n";
                stack_push(buf, a);
                cout << "PUSH A\n";
                break;
            case'-':
                stack_pop(stack);
                cout << "POP B\n";
                cout << "SUB A,B\n";
                stack_push(buf, a);
                cout << "PUSH A\n";
                break;
            default:
                break;
            }
            if (!stack_empty(stack))
            {
                stack_push(buf, stack_get(stack));
                stack_pop(stack);
            }
            a = stack_get(stack);
            stack_pop(stack);
            if (!stack_empty(stack))
            {
                stack_push(stack, a);
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
