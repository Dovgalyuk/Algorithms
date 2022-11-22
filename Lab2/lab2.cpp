#include <iostream>
#include <string>
#include "vector.h"
#include "stack.h"
using namespace std;
int get_priority(char stack)
{
    if (stack == '(' || stack == ')')
    {
        return 1;
    }
   
    if (stack == '+' || stack == '-')
    {
        return 2;
    }
    if (stack == '*' || stack == '/')
    {
        return 3;
    }
}
int main()
{
    string expression; // то, что человек ввёл
    string vivod; // строка на вывод
    while (getline(cin, expression)) // для многоразового ввода
    {
        Stack* stack = stack_create(); 
        for (int i = 0; i < expression.size(); i++) // проверяем каждый элемент входной строки
        {
            switch (get_priority(expression[i])) {
            case 1: if (expression[i] == 40)
            {
                stack_push(stack, expression[i]);
            }
                  else
            {
                while (stack_get(stack) != 40)
                {
                    vivod.push_back(stack_get(stack));
                    stack_pop(stack);
                }
                stack_pop(stack); 
            }
                  break;
            case 2: 
                if (get_priority(stack_get(stack)) >= 2)
                {
                    while (get_priority(stack_get(stack)) >= 2)
                    {
                        vivod.push_back(stack_get(stack));
                        stack_pop(stack);
                    }
                    stack_push(stack, expression[i]);
                }
                else
                {
                    stack_push(stack, expression[i]);
                };
                break;
            case 3:
                if (get_priority(stack_get(stack)) == 3)
                {
                    while (get_priority(stack_get(stack)) == 3)
                    {
                        vivod.push_back(stack_get(stack));
                        stack_pop(stack);
                    }
                    stack_push(stack, expression[i]);
                }
                else
                {
                    stack_push(stack, expression[i]);
                };
                break;
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
