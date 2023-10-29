#include "vector.h"
#include <iostream>
#include "stack.h"
using namespace std;
void task(Stack* stack)
{
    int acc = 0;
    int temp1;
    int temp2;
    bool sign = false;
    string s;
    char c;
    while (cin.get(c))
    {
        if (c == '\n')
        {
            break;
        }
        else
        {
            s += c;
        }
    }
    for (size_t i = 0; i <= s.length(); i++)
    {
        if (s[i] == '*')
        {
            temp1 = stack_get(stack);
            stack_pop(stack);
            temp2 = stack_get(stack) * temp1;
            stack_pop(stack);
            stack_push(stack, temp2);
            sign = true;


        }
        else if (s[i] == '+')
        {
            temp1 = stack_get(stack);
            stack_pop(stack);
            temp2 = stack_get(stack) + temp1;
            stack_pop(stack);
            stack_push(stack, temp2);
            sign = true;
        }
        else if (s[i] == '-')
        {
            temp1 = stack_get(stack);
            stack_pop(stack);
            temp2 = stack_get(stack) - temp1;
            stack_pop(stack);
            stack_push(stack, temp2);
            sign = true;
        }
        else if (s[i] == '/')
        {
            temp1 = stack_get(stack);
            stack_pop(stack);
            temp2 = stack_get(stack) / temp1;
            stack_pop(stack);
            stack_push(stack, temp2);
            sign = true;
        }
        else  if (s[i] == '\0')
        {
            if (sign == true)
            {
                sign = false;
                break;
            }
            stack_push(stack, acc);
            break;

        }
        else   if (s[i] == ' ')
        {
            if (sign == true)
            {
                sign = false;
                continue;
            }
            stack_push(stack, acc);
            acc = 0;
            continue;
        }
        else
        {
            acc = acc * 10 + s[i] - '0';

        }
    }

}




int main()
{
    Stack* stack = stack_create();

    task(stack);
    while (stack_empty(stack) != true)
    {
        cout << stack_get(stack) << endl;
        stack_pop(stack);


    }


}