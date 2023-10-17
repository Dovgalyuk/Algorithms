#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
    Stack* stack = stack_create();
    string input;
    cin >> input;

    for (char ch : input)
    {
        if (isdigit(ch))
        {
            stack_push(stack, ch - '0');
        }
        else if (ch == '+')
        {
            int num1 = stack_get(stack);
            stack_pop(stack);
            int num2 = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, num1 + num2);
        }
        else if (ch == '-')
        {
            int num1 = stack_get(stack);
            stack_pop(stack);
            int num2 = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, num2 - num1);
        }
        else if (ch == '*')
        {
            int num1 = stack_get(stack);
            stack_pop(stack);
            int num2 = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, num1 * num2);
        }
        else if (ch == '/')
        {
            int num1 = stack_get(stack);
            stack_pop(stack);
            int num2 = stack_get(stack);
            stack_pop(stack);
            if (num1 != 0)
            {
                stack_push(stack, num2 / num1);
            }
            else
            {
                cout << "Error" << endl;
                return 1;
            }
        }
        else if (ch == '%')
        {
            int num1 = stack_get(stack);
            stack_pop(stack);
            int num2 = stack_get(stack);
            stack_pop(stack);
            if (num1 != 0)
            {
                stack_push(stack, num2 % num1);
            }
            else
            {
                cout << "Error" << endl;
                return 1;
            }
        }
        else if (ch == '!')
        {
            int num = stack_get(stack);
            stack_pop(stack);
            if (num == 0)
                stack_push(stack, 1);
            else
                stack_push(stack, 0);
        }
        else if (ch == '`')
        {
            int num1 = stack_get(stack);
            stack_pop(stack);
            int num2 = stack_get(stack);
            stack_pop(stack);
            if (num2 > num1)
                stack_push(stack, 1);
            else 
                stack_push(stack, 0);
        }
        else if (ch == ':')
        {
            int num = stack_get(stack);
            stack_push(stack, num);
        }
        else if (ch == '.')
        {
            int num = stack_get(stack);
            stack_pop(stack);
            cout << num << endl;
        }
        else if (ch == '&')
        {
            int num;
            cin >> num;
            stack_push(stack, num);
        }
    }

    stack_delete(stack);
    return 0;
}
