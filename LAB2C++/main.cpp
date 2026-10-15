
#include <cctype>
#include <fstream>
#include <string>

#include "stack.h"

bool is_opening(char ch)
{
    return ch == '(' || ch == '[' || ch == '{' || ch == '<';
}

bool is_closing(char ch)
{
    return ch == ')' || ch == ']' || ch == '}' || ch == '>';
}

bool matches(char opening, char closing)
{
    return (opening == '(' && closing == ')')
        || (opening == '[' && closing == ']')
        || (opening == '{' && closing == '}')
        || (opening == '<' && closing == '>');
}

bool check_brackets(const std::string& sequence)
{
    Stack *stack = stack_create();
    bool correct = true;

    for (char ch : sequence)
    {
        if (std::isspace(static_cast<unsigned char>(ch)))
        {
            continue;
        }

        if (is_opening(ch))
        {
            stack_push(stack, static_cast<int>(ch));
        }
        else if (is_closing(ch))
        {
            if (stack_empty(stack))
            {
                correct = false;
                break;
            }

            char opening = static_cast<char>(stack_get(stack));

            if (!matches(opening, ch))
            {
                correct = false;
                break;
            }

            stack_pop(stack);
        }
        else
        {
            correct = false;
            break;
        }
    }

    if (!stack_empty(stack))
    {
        correct = false;
    }

    stack_delete(stack);
    return correct;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        return 1;
    }

    std::ifstream input(argv[1]);

    if (!input)
    {
        return 1;
    }

    std::ofstream output(argv[2]);

    if (!output)
    {
        return 1;
    }

    std::string sequence;
    char ch;

    while (input.get(ch))
    {
        sequence += ch;
    }

    output << (check_brackets(sequence) ? "YES" : "NO") << '\n';

    return 0;
}
