#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "stack.h"

int get_precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

void emit_operation(char op)
{
    std::cout << "POP A\n";
    std::cout << "POP B\n";
    switch (op)
    {
    case '+':
        std::cout << "ADD A, B\n";
        break;
    case '-':
        std::cout << "SUB A, B\n"; 
        break;
    case '*':
        std::cout << "MUL A, B\n";
        break;
    }
    std::cout << "PUSH A\n";
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error: No input file specified." << std::endl;
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile.is_open())
    {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    Stack *op_stack = stack_create();
    std::string line;

    std::getline(infile, line);
    infile.close();

    std::string current_number;

    for (std::string::size_type i = 0; i < line.length(); ++i)
    {
        char token = line[i];
        if (std::isspace(token))
            continue;
        if (std::isdigit(token))
        {
            current_number += token;
            if (i + 1 == line.length() || !std::isdigit(line[i + 1]))
            {
                std::cout << "PUSH " << current_number << "\n";
                current_number = "";
            }
        }
        else if (token == '(')
        {
            stack_push(op_stack, (Data)token);
        }
        else if (token == ')')
        {
            while (!stack_empty(op_stack) && (char)stack_get(op_stack) != '(')
            {
                emit_operation((char)stack_get(op_stack));
                stack_pop(op_stack);
            }
            stack_pop(op_stack); 
        }
        else 
        {
            while (!stack_empty(op_stack) && 
                   get_precedence((char)stack_get(op_stack)) >= get_precedence(token))
            {
                emit_operation((char)stack_get(op_stack)); 
                stack_pop(op_stack); 
            }
            stack_push(op_stack, (Data)token); 
        }
    }

    while (!stack_empty(op_stack))
    {
        emit_operation((char)stack_get(op_stack));
        stack_pop(op_stack);
    }

    stack_delete(op_stack);
    return 0;
}