#include <fstream>
#include <iostream>
#include <string>
#include "stack.h"
#include "vector.h"

using namespace std;

int word_score(const string& word)
{
    int prices[26] = {
        1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3,
        1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
    };

    int score = 0;

    for (char letter : word)
    {
        if (letter >= 'A' && letter <= 'Z')
        {
            score += prices[letter - 'A'];
        } else if (letter >= 'a' && letter <= 'z')
        {
            score += prices[letter - 'a'];
        }
    }

    return score;
}

int execute(const Vector* commands, Stack* stack, ifstream& input)
{
    size_t position = 0;

    while (position < vector_size(commands))
    {
        int command = vector_get(commands, position);
        ++position;

        if (command == 5)
        {
            if (position >= vector_size(commands))
            {
                cerr << "Missing value after command 5\n";
                return 1;
            }

            int value = vector_get(commands, position);
            stack_push(stack, value % 256);
            ++position;
        }
        else if (command == 7)
        {
            if (stack_empty(stack))
            {
                cerr << "Not enough values for addition\n";
                return 1;
            }

            int first = stack_get(stack);
            stack_pop(stack);

            if (stack_empty(stack))
            {
                cerr << "Not enough values for addition\n";
                return 1;
            }

            int second = stack_get(stack);
            stack_pop(stack);

            stack_push(stack, (first + second) % 256);
        }

        else if (command == 8)
        {
            char symbol;

            if (!input.get(symbol))
            {
                cerr << "Cannot read input character\n";
                return 1;
            }

            stack_push(stack, static_cast<unsigned char>(symbol));
        }

        else if (command == 9)
        {
            if (stack_empty(stack))
            {
                cerr << "Stack is empty\n";
                return 1;
            }

            int value = stack_get(stack);
            stack_pop(stack);

            cout << static_cast<char>(value);
        }

        else if (command == 6)
        {
            if (stack_empty(stack))
            {
                cerr << "Stack is empty\n";
                return 1;
            }

            stack_pop(stack);
        }

        else if (command == 12)
        {
            if (stack_empty(stack))
            {
                cerr << "Stack is empty\n";
                return 1;
            }

            int value = stack_get(stack);
            stack_push(stack, value);
        }

        else if (command == 17)
        {
            return 0;
        }

        else if (command == 10 || command == 11)
        {
            if (stack_empty(stack))
            {
                cerr << "Not enough values\n";
                return 1;
            }

            int first = stack_get(stack);
            stack_pop(stack);

            if (stack_empty(stack))
            {
                cerr << "Not enough values\n";
                return 1;
            }

            int second = stack_get(stack);
            stack_pop(stack);

            if (command == 10)
            {
                int result = (second - first + 256) % 256;
                stack_push(stack, result);
            }
            else
            {
                stack_push(stack, first);
                stack_push(stack, second);
            }
        }

        else if (command == 13 || command == 14)
        {
            if (position >= vector_size(commands))
            {
                cerr << "Missing jump distance\n";
                return 1;
            }

            if (stack_empty(stack))
            {
                cerr << "Stack is empty\n";
                return 1;
            }

            int value = stack_get(stack);
            stack_pop(stack);

            size_t distance = vector_get(commands, position);
            ++position;

            bool jump = (command == 13 && value == 0)
                     || (command == 14 && value != 0);

            if (jump)
            {
                if (distance > vector_size(commands) - position)
                    return 0;

                position += distance;
            }
        }

        else if (command == 15 || command == 16)
        {
            if (position >= vector_size(commands))
            {
                cerr << "Missing jump distance\n";
                return 1;
            }

            if (stack_empty(stack))
            {
                cerr << "Stack is empty\n";
                return 1;
            }

            int value = stack_get(stack);
            stack_pop(stack);

            size_t distance = vector_get(commands, position);
            ++position;

            bool jump = (command == 15 && value == 0)
                     || (command == 16 && value != 0);

            if (jump)
            {
                if (distance > position)
                {
                    cerr << "Jump before script start\n";
                    return 1;
                }

                position -= distance;
            }
        }
    }

    return 0;
}

bool read_word(ifstream& file, string& word)
{
    word.clear();
    char symbol;

    while (file.get(symbol))
    {
        bool letter = (symbol >= 'A' && symbol <= 'Z')
                   || (symbol >= 'a' && symbol <= 'z');

        if (letter)
        {
            word += symbol;
        }
        else if (!word.empty())
        {
            return true;
        }
    }

    return !word.empty();
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: Beatnik <script_file> <input_file> \n";
        return 1;
    }

    ifstream script(argv[1]);
    ifstream input(argv[2]);

    if (!script)
    {
        cerr << "Cannot open script file\n";
        return 1;
    }

    if (!input)
    {
        cerr << "Cannot open input file\n";
        return 1;
    }

    Vector* commands = vector_create();

    string word;

    while (read_word(script, word))
    {
        int score = word_score(word);
        size_t size = vector_size(commands);

        vector_resize(commands, size + 1);
        vector_set(commands, size, score);

    }

    Stack* stack = stack_create();

    int result = execute(commands, stack, input);

    stack_delete(stack);
    vector_delete(commands);

    return result;
}