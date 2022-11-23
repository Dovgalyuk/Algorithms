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
            case 1: case 2: case 3:
                if (get_priority(stack_get(stack)) >= get_priority(expression[i]))
                {
                    if (expression[i] == '(')
                    {
                        stack_push(stack, expression[i]);
                        break;
                    }
                    if (expression[i] == ')')
                    {
                        while (stack_get(stack) != '(')
                        {
                            vivod.push_back(stack_get(stack));
                            stack_pop(stack);
                        }
                        stack_pop(stack);
                        break;
                    }
                    else
                    {
                        while (get_priority(stack_get(stack)) >= get_priority(expression[i]))
                        {
                            vivod.push_back(stack_get(stack));
                            stack_pop(stack);
                        }
                        stack_push(stack, expression[i]);
                    }
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
