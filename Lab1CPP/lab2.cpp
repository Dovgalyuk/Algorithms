#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

//Знаки операций будут иметь приоритеты: "(", ")" - 1; "+", "-" - 2; "*", "/" - 3.
int get_level_operation(char operation) //Функция для получения уровня приоритета
{
    if (operation == '(' || operation == ')')
    {
        return 1;
    }
    if (operation == '+' || operation == '-')
    {
        return 2;
    }
    if (operation == '*' || operation == '/')
    {
        return 3;
    }
    return 0;
}

int main()
{
    string input_expression, output_expression; //Переменные для хранения входного и выходного выражения
    Stack* stack_for_operation_signs = stack_create(); //Стек для хранения знаков операций

    std::cout << "Enter expression to convert: ";
    getline(cin, input_expression); //Ввод строки с выражением

    for (size_t i = 0; i < input_expression.size(); i++) //Перебор введенной строки по символам
    {
        switch (input_expression[i]) //Конструкция используется для сравнения символов из выражения
        {
        case '(': //Если открывающаяся скобка
            stack_push(stack_for_operation_signs, input_expression[i]); //Добавление в стек знака
            break; //Выход из switch
        case ')': //Если закрывающаяся скобка
            if (!stack_empty(stack_for_operation_signs)) //Если стек не пустой
            {
                while (get_level_operation(stack_get(stack_for_operation_signs)) >= 1) //Пока не встретится открывающаяся скобка в стеке
                {
                    if (stack_get(stack_for_operation_signs) == '(') //Если на вершине стека открывающаяся скобка
                    {
                        stack_pop(stack_for_operation_signs); //Удалить элемент на вершине стека
                        break; //Выйти из цикла while
                    }
                    output_expression += stack_get(stack_for_operation_signs); //Добавить в выходное выражение элемент из вершины стека
                    stack_pop(stack_for_operation_signs); //Удалить элемент на вершине стека
                }
            }            
            break; //Выход из switch
        case '*': //Если знак умножения
        case '/': //Или знак деления
        case '+': //Или знак сложения
        case '-': //Или знак вычитания
            if (!stack_empty(stack_for_operation_signs)) //Если стек не пустой
            {
                while (get_level_operation(stack_get(stack_for_operation_signs)) >= get_level_operation(input_expression[i])) //Пока уровень приоритета элемента на вершине стека больше или равен текущему элементу из строки
                {
                    output_expression += stack_get(stack_for_operation_signs); //Добавить в выходное выражение элемент из вершины стека
                    stack_pop(stack_for_operation_signs); //Удалить элемент на вершине стека
                }
                stack_push(stack_for_operation_signs, input_expression[i]); //Добавление в стек текущего элемента из строки
            }
            break; //Выход из switch
        default: //Если символ, отличающийся от символа операции (т.е. цифра или переменная)
            output_expression += input_expression[i]; //Добавление в выходное выражение
            break; //Выход из switch
        }
    }

    while (!stack_empty(stack_for_operation_signs)) //Пока стек не пустой
    {
        output_expression += stack_get(stack_for_operation_signs); //Добавить в выходное выражение элемент из вершины стека
        stack_pop(stack_for_operation_signs); //Удалить элемент на вершине стека
    }

    cout << endl << output_expression; //Вывод выходного выражения

}