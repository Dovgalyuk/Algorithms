#include <iostream>
#include <string>
#include "vector.h"
#include "stack.h"
using namespace std;
int main()
{
    string expression;
    string vivod;
    while (getline(cin, expression))
    {
        Stack* stack = stack_create();
        for (int i = 0; i < expression.size(); i++)
        {
            switch (expression[i]) {
            case '+': 
                     if (stack_prior(stack) >= 2)
            {
                         while (stack_prior(stack) >= 2)
                         {
                             vivod.push_back(stack_get(stack));
                             stack_pop(stack);
                         }
                         stack_push(stack, '+');
            }
                    else
            {
                stack_push(stack, '+');
            }; break;
            case '-':
                if (stack_prior(stack) >= 2)
            {
                while (stack_prior(stack) >= 2)
                {
                    vivod.push_back(stack_get(stack));
                    stack_pop(stack);
                }
                stack_push(stack, '-');
            }
            
                else
            {
                stack_push(stack, '-');
            }; break;
            case '*':   if (stack_prior(stack) == 3)
            {
                while (stack_prior(stack) == 3)
                {
                    vivod.push_back(stack_get(stack));
                    stack_pop(stack);
                }
                stack_push(stack, '*');
            }
                    else
            {
                stack_push(stack, '*');
            } break;
            case '/': if (stack_prior(stack) == 3)
            {
                while (stack_prior(stack) == 3)
                {
                    vivod.push_back(stack_get(stack));
                    stack_pop(stack);
                }
                stack_push(stack, '/');
            }
                    else
            {
                stack_push(stack, '/');
            }; break;
            case '(': stack_push(stack, '('); break;
            case ')': while (stack_get(stack) != '(')
            {
                vivod.push_back(stack_get(stack));
                stack_pop(stack);
            }
            stack_pop(stack); break;
            default:
                vivod.push_back(expression[i]);

            }
        }
        while (!stack_empty(stack))
        {
            vivod.push_back(stack_get(stack));
            stack_pop(stack);
        }

        cout << vivod << endl;
        vivod.clear();
        stack_delete(stack);
    }
    
    

}
