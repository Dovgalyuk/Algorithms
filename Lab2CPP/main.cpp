#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include "stack.h"

using namespace std;

int prec(int op)
{
    if (op == '*')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

void emit_op(char c)
{
    cout << "POP A\n";
    cout << "POP B\n";
    if (c == '+')
        cout << "ADD A, B\n";
    else if (c == '-')
        cout << "SUB A, B\n";
    else if (c == '*')
        cout << "MUL A, B\n";
    cout << "PUSH A\n";
}

int main(int argc, char** argv)
{
    string s;
    if (argc > 1)
    {
        ifstream in(argv[1]);
        if (in.good())
        {
            getline(in, s);
        }
        else
        {
            s = argv[1];
        }
    }
    else
    {
        if (!getline(cin, s))
            return 0;
    }

    // ќдин проход: лексинг, шунтирующий алгоритм, немедленна€ генераци€
    Stack* op = stack_create();   //стек операторов: храним char как int

    for (size_t i = 0; i < s.size();)
    {
        char c = s[i];

        if (isspace(c))
        {
            i++;
            continue;
        }

        if (isdigit(c))
        {
            int val = 0;
            while (i < s.size() && isdigit(s[i]))
            {
                val = val * 10 + (s[i] - '0');
                i++;
            }
            cout << "PUSH " << val << "\n";
        }
        else
        {
            i++;

            if (c == '(')
            {
                stack_push(op, static_cast<int>('('));
            }
            else if (c == ')')
            {
                while (!stack_empty(op) && stack_get(op) != static_cast<int>('('))
                {
                    char topc = static_cast<char>(stack_get(op));
                    emit_op(topc);
                    stack_pop(op);
                }
                if (!stack_empty(op) && stack_get(op) == static_cast<int>('('))
                {
                    stack_pop(op); // удалить '('
                }
                else
                {
                    //несоответствие скобок Ч можно просто завершить
                    stack_delete(op);
                    return 1;
                }
            }
            else if (c == '+' || c == '-' || c == '*')
            {
                int cur = static_cast<int>(c);
                while (!stack_empty(op))
                {
                    int top = stack_get(op);
                    if (top == static_cast<int>('('))
                        break;
                    if (prec(top) >= prec(cur))
                    {
                        char topc = static_cast<char>(top);
                        emit_op(topc);
                        stack_pop(op);
                    }
                    else
                    {
                        break;
                    }
                }
                stack_push(op, cur);
            }
            else
            {
                // некорректный символ Ч просто выходим с ошибкой
                stack_delete(op);
                return 1;
            }
        }
    }

    //ƒопечатываем оставшиес€ операторы
    while (!stack_empty(op))
    {
        int top = stack_get(op);
        if (top == static_cast<int>('('))
        {
            stack_delete(op);
            return 1;
        }
        char c = static_cast<char>(top);
        emit_op(c);
        stack_pop(op);
    }

    stack_delete(op);
}
