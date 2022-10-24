#include <iostream>
#include "stack.h"
#include "list.h"
#include <cctype>
#include <string>

using namespace std;

void muladdsub(Stack *stack)
{
    Stack* buf = stack_create();
    int a;
    while (!stack_empty(stack))
    {
        if (stack_get(stack) == '*')
        {
            stack_pop(stack);
            cout << "POP A\n";
            a = stack_get(stack);
            stack_pop(stack);
            cout << "POP B\n";
            stack_pop(buf);
            cout << "MUL A, B\n";
            stack_push(buf, a);
            cout << "PUSH A\n";
        }
        else if (!stack_empty(stack))
        {
            stack_push(buf, stack_get(stack));
            stack_pop(stack);
        }
    }
    a = stack_get(buf);
    stack_pop(buf);
    while (!stack_empty(buf))
    {
        stack_push(buf, a);
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
        case '+':
            stack_pop(buf);
            cout << "POP B\nADD A, B\n";
            stack_pop(stack);
            break;
        case '-':
            stack_pop(buf);
            cout << "POP B\nSUB A, B\n";
            stack_pop(stack);
            break;
        default:
            break;
        }
        stack_push(stack, a);
        cout << "PUSH A\n";
        if (!stack_empty(buf))
        {
            stack_push(stack, stack_get(buf));
            stack_pop(buf);
        }
    }
    stack_pop(stack);
}

void findstaples(Stack* stack)
{
    Stack* staples = stack_create();
    while (stack_get(stack) != '(')
    {
        stack_push(staples, stack_get(stack));
        stack_pop(stack);
    }
    stack_pop(stack);
    muladdsub(staples);
    stack_delete(staples);
}

void bufstack(Stack* stack)
{
    Stack* buf = stack_create();
    int a;
    while (stack_get(stack) != 0)
    {
        if (stack_get(stack) == ')')
        {
            findstaples(buf);
        }
        if (stack_get(stack) != 0)
        {
            stack_push(buf, stack_get(stack));
            if (stack_get(stack) <= '9' && stack_get(stack) >= '0')
                cout << "PUSH " << char(stack_get(stack)) << "\n";
            stack_pop(stack);
        }
    }
    muladdsub(buf);
    stack_delete(buf);
}

void third(string& str)
{
    Stack* stack = stack_create();
    for (int i = str.length(); i >= 0;i--)
    {
        stack_push(stack, str[i]);
    }
    bufstack(stack);
    stack_delete(stack);
}

int main()
{
    string str;
    cout << "Enter string :\n";
    cin >> str;
    third(str);
}
