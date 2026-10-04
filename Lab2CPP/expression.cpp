#include <climits>
#include <fstream>
#include <iostream>

#include "stack.h"

using namespace std;

int priority(int sign)
{
    if (sign == '+' || sign == '-')
        return 1;
    if (sign == '*' || sign == '/')
        return 2;
    return 0;
}

bool calculate(Stack *numbers, Stack *signs)
{
    if (stack_empty(numbers) || stack_empty(signs))
        return false;

    long long right = stack_get(numbers);
    stack_pop(numbers);
    if (stack_empty(numbers))
        return false;

    long long left = stack_get(numbers);
    stack_pop(numbers);
    int sign = stack_get(signs);
    stack_pop(signs);

    long long result;
    if (sign == '+')
        result = left + right;
    else if (sign == '-')
        result = left - right;
    else if (sign == '*')
        result = left * right;
    else if (sign == '/' && right != 0)
        result = left / right;
    else
        return false;

    if (result < INT_MIN || result > INT_MAX)
        return false;

    stack_push(numbers, static_cast<int>(result));
    return true;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Использование: Lab2CPPExpression входной_файл.txt\n";
        return 1;
    }

    ifstream input(argv[1]);
    if (!input)
    {
        cerr << "Ошибка: не удалось открыть входной файл\n";
        return 1;
    }

    Stack *numbers = stack_create();
    Stack *signs = stack_create();
    bool valid = true;
    bool need_number = true;
    char symbol;

    while (valid && input >> symbol)
    {
        if (symbol >= '0' && symbol <= '9')
        {
            if (!need_number)
                valid = false;
            else
            {
                input.putback(symbol);
                int number;
                if (input >> number)
                {
                    stack_push(numbers, number);
                    need_number = false;
                }
                else
                    valid = false;
            }
        }
        else if (symbol == '(' && need_number)
            stack_push(signs, symbol);
        else if (symbol == ')' && !need_number)
        {
            while (valid && !stack_empty(signs) && stack_get(signs) != '(')
                valid = calculate(numbers, signs);

            if (stack_empty(signs))
                valid = false;
            else
                stack_pop(signs);
        }
        else if (priority(symbol) != 0 && !need_number)
        {
            while (valid && !stack_empty(signs) && priority(stack_get(signs)) >= priority(symbol))
                valid = calculate(numbers, signs);

            stack_push(signs, symbol);
            need_number = true;
        }
        else
            valid = false;
    }

    if (need_number)
        valid = false;

    while (valid && !stack_empty(signs))
        valid = calculate(numbers, signs);

    int result = stack_get(numbers);
    stack_delete(numbers);
    stack_delete(signs);

    if (!valid)
    {
        cerr << "Ошибка в выражении\n";
        return 1;
    }

    cout << result << '\n';
    return 0;
}
