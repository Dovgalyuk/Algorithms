#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "stack.h"

int get_precedence(char op)
{
    if (op == '*')
    {
        return 2;
    }
    if (op == '+' || op == '-')
    {
        return 1;
    }
    return 0;
}

void emit_operation(char op)
{
    std::cout << "POP A\n";
    std::cout << "POP B\n";
    if (op == '+')
    {
        std::cout << "ADD A, B\n";
        std::cout << "PUSH A\n";
    }
    else if (op == '-')
    {
        std::cout << "SUB B, A\n";
        std::cout << "PUSH B\n";
    }
    else if (op == '*')
    {
        std::cout << "MUL A, B\n";
        std::cout << "PUSH A\n";
    }
}

void process_expression(const std::string &expr)
{
    Stack *op_stack = stack_create();
    size_t i = 0;

    while (i < expr.length())
    {
        if (isspace(static_cast<unsigned char>(expr[i])))
        {
            ++i;
            continue;
        }

        if (isdigit(static_cast<unsigned char>(expr[i])))
        {
            std::string number;
            while (i < expr.length() && isdigit(static_cast<unsigned char>(expr[i])))
            {
                number += expr[i];
                ++i;
            }
            std::cout << "PUSH " << number << "\n";
            continue;
        }

        if (expr[i] == '(')
        {
            stack_push(op_stack, '(');
            ++i;
            continue;
        }

        if (expr[i] == ')')
        {
            while (!stack_empty(op_stack) && stack_get(op_stack) != '(')
            {
                char op = static_cast<char>(stack_get(op_stack));
                stack_pop(op_stack);
                emit_operation(op);
            }
            if (!stack_empty(op_stack) && stack_get(op_stack) == '(')
            {
                stack_pop(op_stack);
            }
            ++i;
            continue;
        }

        if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*')
        {
            char current_op = expr[i];
            while (!stack_empty(op_stack) && stack_get(op_stack) != '(' &&
                   get_precedence(static_cast<char>(stack_get(op_stack))) >= get_precedence(current_op))
            {
                char op = static_cast<char>(stack_get(op_stack));
                stack_pop(op_stack);
                emit_operation(op);
            }
            stack_push(op_stack, current_op);
            ++i;
            continue;
        }

        ++i;
    }

    while (!stack_empty(op_stack))
    {
        char op = static_cast<char>(stack_get(op_stack));
        stack_pop(op_stack);
        if (op != '(' && op != ')')
        {
            emit_operation(op);
        }
    }

    stack_delete(op_stack);
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        std::ifstream file(argv[1]);
        if (!file.is_open())
        {
            std::cerr << "Cannot open file: " << argv[1] << "\n";
            return 1;
        }
        std::string line;
        while (std::getline(file, line))
        {
            if (!line.empty())
            {
                process_expression(line);
            }
        }
    }
    else
    {
        std::string line;
        while (std::getline(std::cin, line))
        {
            if (!line.empty())
            {
                process_expression(line);
            }
        }
    }

    return 0;
}
