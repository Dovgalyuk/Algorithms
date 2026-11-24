#include <fstream>
#include <iostream>
#include <string>
#include "stack.h"

static char opening_for(char c)
{
    switch (c)
    {
    case ')': return '(';
    case ']': return '[';
    case '}': return '{';
    case '>': return '<';
    default: return 0;
    }
}

static bool is_opening(char c)
{
    return c == '(' || c == '[' || c == '{' || c == '<';
}

static bool check_brackets(const std::string &line)
{
    Stack *stack = stack_create();
    bool ok = true;
    for (char c : line)
    {
        if (is_opening(c))
        {
            stack_push(stack, c);
        }
        else if (char open = opening_for(c))
        {
            if (stack_empty(stack) || stack_get(stack) != open)
            {
                ok = false;
                break;
            }
            stack_pop(stack);
        }
    }
    if (!stack_empty(stack))
        ok = false;
    stack_delete(stack);
    return ok;
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " input output\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Can't open input file\n";
        return 1;
    }
    std::string line;
    std::getline(input, line);

    std::ofstream output(argv[2]);
    output << (check_brackets(line) ? "YES" : "NO") << '\n';
}
