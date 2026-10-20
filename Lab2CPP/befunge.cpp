#include <climits>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include "stack.h"

using namespace std;

//извлечение из пустого стека = 0
Data pop_value(Stack *stack)
{
    if (stack_empty(stack))
        return 0;
    Data value = stack_get(stack);
    stack_pop(stack);
    return value;
}

// кладёт результат в стек, если он помещается в Data
bool push_checked(Stack *stack, long long value)
{
    if (value < INT_MIN || value > INT_MAX)
        return false;
    stack_push(stack, static_cast<Data>(value));
    return true;
}

// выполняет скрипт, возвращает 0 при успехе
int run(istream &input, Stack *stack)
{
    char c;
    while (input.get(c))
    {
        if (c >= '0' && c <= '9')
        {
            stack_push(stack, c - '0');
            continue;
        }

        long long a, b;
        switch (c)
        {
        case '+':
            a = pop_value(stack);
            b = pop_value(stack);
            if (!push_checked(stack, b + a))
            {
                cout << "overflow\n";
                return 1;
            }
            break;
        case '-':
            a = pop_value(stack);
            b = pop_value(stack);
            if (!push_checked(stack, b - a))
            {
                cout << "overflow\n";
                return 1;
            }
            break;
        case '*':
            a = pop_value(stack);
            b = pop_value(stack);
            if (!push_checked(stack, b * a))
            {
                cout << "overflow\n";
                return 1;
            }
            break;
        case '/':
        case '%':
            a = pop_value(stack);
            b = pop_value(stack);
            if (a == 0)
            {
                cout << "division by zero\n";
                return 1;
            }
            if (!push_checked(stack, c == '/' ? b / a : b % a))
            {
                cout << "overflow\n";
                return 1;
            }
            break;
        case '!':
            stack_push(stack, pop_value(stack) == 0 ? 1 : 0);
            break;
        case '`':
            a = pop_value(stack);
            b = pop_value(stack);
            stack_push(stack, b > a ? 1 : 0);
            break;
        case ':':
        {
            Data value = pop_value(stack);
            stack_push(stack, value);
            stack_push(stack, value);
            break;
        }
        case '.':
            cout << pop_value(stack) << "\n";
            break;
        case '&':
            stack_push(stack, rand() % 10);
            break;
        default:
            break;
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "usage: " << argv[0] << " input.txt\n";
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open())
    {
        cout << "cannot open file " << argv[1] << "\n";
        return 1;
    }

    srand(static_cast<unsigned>(time(nullptr)));

    Stack *stack = stack_create();
    int result = run(input, stack);
    stack_delete(stack);
    return result;
}
