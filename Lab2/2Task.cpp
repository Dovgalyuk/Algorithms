#include <iostream>
#include <string>
#include "list.h"
#include "stack.h"
using std::cin; using std::cout; using std::string;

int main();

int Priority(const char &ch)   // Получаем приоритеты для операторов
{
    switch (ch)
    {
    case '(':
        return 0;
    case ')':
        return 1;
    case '+':
    case '-':
        return 3;
        break;
    case '*':
    case '/':
        return 4;
        break;
    }
}

string ReversePolishEntry(string& inputStr)                           // Операнды записыаем в результирующую строку, а операторы в стек 
{
    Stack* stack = stack_create();                                   // Создаем стек
    string resulstStr;
    
    for (int i = 0; i < inputStr.size(); i++)
    {
        if (inputStr[i] != '(' && inputStr[i] != ')')              // Если в выражении отсутствуют круглые скобки
        {
            if (stack_empty(stack) && !isalpha(inputStr[i]))     // Если стек пуст и символ НЕ буква
            {
                stack_push(stack, inputStr[i]);                // Добавить в него оператор
            }
            else if (isalpha(inputStr[i]))                   // Если символ буква
            {
                resulstStr += inputStr[i];                 // Записываем ее в результирующую строку
            }
            else if (Priority(inputStr[i]) > Priority(stack_get(stack)))   // Если приоритет оператора > последенему в стеке оператору
            {
                stack_push(stack, inputStr[i]);                           // Записываем его в сек
            }
            else                                                         
            {
                while (!stack_empty(stack))                // Пока стек НЕ пуст
                {
                    resulstStr += stack_get(stack);      // Записываем его в результирующую строку
                    stack_pop(stack);                   // Удаляем последний элемент стека, чтобы выйти из цикла
                }
                stack_push(stack, inputStr[i]);       // Чтобы не потеря последний оператор, записываем его в стек
            }
        }
        else                                          // Если в выражении присутствуют круглые скобки        
        {
            if (inputStr[i] == ')')                 // Если находим ')'
            {
                while (stack_get(stack) != '(')   // Пока не дойдем до '('
                {
                    resulstStr += stack_get(stack);   // Выталкиваем все операторы из стека в результирующую строку
                    stack_pop(stack);                // Удаляем выталкиваемые элементы из стека
                }
                stack_pop(stack);                  // Когда доходим до '(', удаляем ее.
            }
            else                                 // Если НЕ находим ')'
            {
                stack_push(stack, inputStr[i]);  // Добавляем оператор в стек
            }
        }
    }
    while (!stack_empty(stack))                // Пока стек НЕ пуст
    {
        resulstStr += stack_get(stack);      // Записываем операторы из стека в результирующую строку
        stack_pop(stack);                   // Удаляем последний элемент стека, чтобы выйти из цикла
    }
    
    stack_delete(stack);                 // Удаляем стек
    return  resulstStr;
}

int main()
{
  
    string inputStr, outputStr;

    cout << "\n\tEnter the line: ";
    cin >> inputStr; cout << "\n";
  
    cout << "\n\tReverse Polish entry: ";
    outputStr = { ReversePolishEntry(inputStr) };

    cout << outputStr << "\n\n";
    
    system("pause");
    system("cls");
    main();
}



