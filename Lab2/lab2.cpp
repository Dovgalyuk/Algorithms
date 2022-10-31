#include <iostream>
#include "stack.h"
#include "list.h"
#include <cctype>
#include <string>

using namespace std;

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

void findstaples(Stack* stack)
{
    Stack* staples = stack_create();
    while (stack_get(stack) != '(')
    {
        stack_push(staples, stack_get(stack));
        if (stack_get(staples) == '*')
            muladdsub(staples);
        stack_pop(stack);
    }
    stack_pop(stack);
    while(!stack_empty(staples))
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
            findstaples(stack);
        if (str[i] <= '9' && str[i] >= '0')
            cout << "PUSH " << str[i] << "\n";
        if (!isdigit(str[i]) && str[i] != ')')
            stack_push(stack, str[i]);
        if(i>0)
            if (str[i-1] == '*' && int(str.find('(')) < 0)
                muladdsub(stack);
    }
    while(!stack_empty(stack))
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
