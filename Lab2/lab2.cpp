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

void third(string& str)
{
    Stack* buf = stack_create();
    int a;
    for (int i = 0; i < str.length();i++)
    {
        if (str[i] == ')')
        {
            findstaples(buf);
        }
        stack_push(buf, str[i]);
        if (str[i] <= '9' && str[i] >= '0')
            cout << "PUSH " << str[i] << "\n";
    }
    muladdsub(buf);
    stack_delete(buf);
}

int main()
{
    string str;
    cout << "Enter string :\n";
    cin >> str;
    third(str);
}
