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
    char c=0;
    for (size_t i = 0; c!='\n'; i++)
    {
     
        cin.get(c);
        
        if (c == '*')
        {
            temp1 = stack_get(stack);
            stack_pop(stack);
            temp2 = stack_get(stack) * temp1;
            stack_pop(stack);
            stack_push(stack, temp2);
            sign = true;


        }
        else if (c == '+')
        {
            temp1 = stack_get(stack);
            stack_pop(stack);
            temp2 = stack_get(stack) + temp1;
            stack_pop(stack);
            stack_push(stack, temp2);
            sign = true;
        }
        else if (c == '-')
        {
            temp1 = stack_get(stack);
            stack_pop(stack);
            temp2 = stack_get(stack) - temp1;
            stack_pop(stack);
            stack_push(stack, temp2);
            sign = true;
        }
        else if (c == '/')
        {
            temp1 = stack_get(stack);
            stack_pop(stack);
            temp2 = stack_get(stack) / temp1;
            stack_pop(stack);
            stack_push(stack, temp2);
            sign = true;
        }
        else  if (c == '\n')
        {
            if (sign == true)
            {
                sign = false;
                break;
            }
            stack_push(stack, acc);
            break;

        }
        else   if (c == ' ')
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
            acc = acc * 10 + c - '0';

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
    stack_delete(stack);

}