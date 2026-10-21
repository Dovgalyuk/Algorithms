#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "../LibraryCPP/stack.h"

using namespace std;

string toLower(string text)
{
    for (char &c : text)
    {
        c = static_cast<char>(
            tolower(static_cast<unsigned char>(c))
        );
    }

    return text;
}

bool checkTags(istream &input)
{
    Stack *stack = stack_create();
    string tag;
    bool correct = true;

    while (getline(input, tag))
    {
        if (!tag.empty() && tag.back() == '\r')
            tag.pop_back();

        if (tag.empty())
            continue;

        if (tag.size() < 3 || tag.front() != '<' ||
            tag.back() != '>')
        {
            correct = false;
            break;
        }

        bool closing = tag[1] == '/';

        string name = closing
            ? tag.substr(2, tag.size() - 3)
            : tag.substr(1, tag.size() - 2);

        if (name.empty())
        {
            correct = false;
            break;
        }

        name = toLower(name);

        if (!closing)
        {
            stack_push(stack, name);
        }
        else
        {
            if (stack_empty(stack) || stack_get(stack) != name)
            {
                correct = false;
                break;
            }

            stack_pop(stack);
        }
    }

    if (!stack_empty(stack))
        correct = false;

    stack_delete(stack);

    return correct;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Usage: Lab2CPP <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);

    if (!input.is_open())
    {
        cout << "Cannot open file" << endl;
        return 1;
    }

    cout << (checkTags(input) ? "YES" : "NO") << endl;

    return 0;
}

