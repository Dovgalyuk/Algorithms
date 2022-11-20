#include <iostream>
#include "stack.h"
#include "list.h"
#include <cctype>
#include <string>


using namespace std;

int operation(const char& a) // приоритет операции (чем выше, тем меньше число, чтобы укладывать в стек)
{
    if (a == '*' || a == '/') {
        return 3;
    }
    if (a == '+' || a == '-') {
        return 4;
    }
}

string ToPostfix(string str)
{
    Stack* s = stack_create();
    string str2;
    for (char c : str)
    { 
        if (c == '(') // помещаем в стек "("
        {
            stack_push(s, c);
        }
        else if (c == ')')
        {
            while (stack_get(s) != '(') // извлекаем элементы, пока не найдем "(" для ")"
            {
                str2.push_back(stack_get(s));
                stack_pop(s);
            }
            stack_pop(s);
        }
        else if (isdigit(c)) // если цифра, то в её конец новой строки
        {
            str2.push_back(c);
        }
        else { // если оператор
            while (!stack_empty(s) && operation(c) >= operation(stack_get(s)))
            {
                str2.push_back(stack_get(s)); // извлекаем оператор с более высоким или равным приоритетом, и его в конец новой строки
                stack_pop(s);
            }
            stack_push(s, c); // текущий оператор на вершину стека
        }
    }
    while (!stack_empty(s)) // вытаскиваем все из стека и помещаем в конец новой строки
    {
        str2.push_back(stack_get(s));
        stack_pop(s);
    }
    stack_delete(s);
    return str2; // постфиксное выражение готово
}

int vichislenie(string str2)
{
    Stack* s = stack_create();
    for (char c : str2)
    {
        if (isdigit(c)) // если цифра, помещаем в стек
        {
            stack_push(s, c - '0');
        }
        else { // если оператор
            int x = stack_get(s); 
            stack_pop(s);

            int y = stack_get(s);
            stack_pop(s);
            if (c == '+') { // результаты вычислений обратно в стек и так до конца
                stack_push(s, y + x);
            }
            else if (c == '-') {
                stack_push(s, y - x);
            }
            else if (c == '*') {
                stack_push(s, y * x);
            }
            else if (c == '/') {
                stack_push(s, y / x);
            }
        }
    }
    return stack_get(s); // в стеке остался только результат выражения
    stack_delete(s);
}

int main()
{
    setlocale(LC_ALL, "RU");
    string str, str2;
   
    cout << "Введите выражение: ";
    cin >> str;
    str2 = ToPostfix(str);
    cout << vichislenie(str2);
}

