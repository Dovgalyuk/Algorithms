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
    else
    {
        return 0; // если пустой
    }
}
int main()
{
    string expression; // строка на ввод
    string outp; // строка на вывод
    while (getline(cin, expression)) // для многоразового ввода
    {
        Stack* stack = stack_create(); 
        for (int i = 0; i < expression.size();) // проверяем каждый элемент входной строки
        {
            while (get_priority(expression[i]) >= 1 && get_priority(expression[i]) <= 3)
            {
                if (expression[i] == '(')
                {
                    while (expression[i] == '(')
                    {
                        stack_push(stack, expression[i]);
                        i++;
                    }
                    outp.push_back(expression[i]); // чтобы буква не попала в else
                    i++;
                }
                if (expression[i] == ')')
                {
                    while (stack_get(stack) != '(')
                    {
                        outp.push_back(stack_get(stack));
                        stack_pop(stack);
                    }
                    stack_pop(stack);
                    i++;
                }
                else
                {           
                        while (get_priority(stack_get(stack)) >= get_priority(expression[i]))
                        {    
                            outp.push_back(stack_get(stack));
                            stack_pop(stack);
                        }
                        stack_push(stack, expression[i]);
                        i++;
                }
            }

            outp.push_back(expression[i]);  
            i++;
                     
        }
        while (!stack_empty(stack))
        {
            outp.push_back(stack_get(stack));
            stack_pop(stack);
        }
        cout << outp << endl;
        outp.clear();
        stack_delete(stack);
    }       
}
