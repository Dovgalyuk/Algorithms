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
            cout << "POP B\n";
            cout << "MUL A, B\n";
            cout << "PUSH A\n";
        }
        else if (!stack_empty(stack))
        {
            stack_push(buf, stack_get(stack));
            stack_pop(stack);
        }
    }
    while (!stack_empty(buf))
    {
        cout << "POP A\n";
        switch (stack_get(buf))
        {
        case '+':
            stack_pop(buf);
            cout << "POP B\nADD A, B\n";
            break;
        case '-':
            stack_pop(buf);
            cout << "POP B\nSUB A, B\n";
            break;
        default:
            break;
        }
        cout << "PUSH A\n";
    }
    stack_delete(buf);
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

void third(string str)
{
    Stack* stack = stack_create();
    int a;
    for (int i = 0; i < str.length();i++)
    {
        if (str[i] == ')')
        {
            findstaples(stack);
        }
        if(!isdigit(str[i])&&str[i]!=')')
            stack_push(stack, str[i]);
        if (str[i] <= '9' && str[i] >= '0')
            cout << "PUSH " << str[i] << "\n";
    }
    muladdsub(stack);
    stack_delete(stack);
}

int main()
{
    string str;
    cout << "Enter string :\n";
    cin >> str;
    third(str);
}
