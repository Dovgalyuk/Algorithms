#include "../LibraryCPPTemplate/vector.h"
#include "../LibraryCPPTemplate/stack.h"
#include <iostream>
#include <fstream>
#include <string>

struct Pointer
{
    int row;
    int col;
    int direction;
};

void movePointer(Pointer &pointer)
{
    pointer.row++;
    pointer.col += pointer.direction;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Too few arguments\n";
        return 1;
    }

    std::ifstream scriptFile(argv[1]);
    std::ifstream inputFile(argv[2]);

    if (!scriptFile.is_open() || !inputFile.is_open())
    {
        std::cerr << "File wasn't opened\n";
        return 1;
    }

    Vector<std::string> script;

    std::string line;

    while (std::getline(scriptFile, line))
    {
        size_t index = script.size();
        script.resize(index + 1);
        script.set(index, line);
    }

    if (script.size() == 0)
    {
        std::cerr << "Script is empty";
        return 1;
    }

    Pointer pointer = {0, -1, -1};
    std::string firstLine = script.get(0);
    int startCount = 0;

    for (size_t col = 0; col < firstLine.size(); col++)
    {
        if (firstLine[col] == '*')
        {
            pointer.col = static_cast<int>(col);
            startCount++;
        }
    }
    if (startCount != 1)
    {
        std::cerr << "Invalid start position\n";
        return 1;
    }

    Stack<int> values;
    Stack<Pointer> branches;
    bool printMode = false;

    Pointer ret = {0, 0, -1};

    while (true)
    {
        if (pointer.row < 0 ||
            pointer.row >= static_cast<int>(script.size()) ||
            pointer.col < 0 ||
            pointer.col >= static_cast<int>(script.get(pointer.row).size()))
        {
            std::cerr << "Pointer out of range";
            return 1;
            return 1;
        }
        char c = script.get(pointer.row)[pointer.col];

        if (printMode && c != '"')
        {
            std::cout << c;
            movePointer(pointer);
            continue;
        }

        switch (c)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            values.push(c - '0');
            break;
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
            values.push(c - 'A' + 10);
            break;
        case '+':
        {
            int a = values.get();
            values.pop();

            int b = values.get();
            values.pop();

            values.push((a + b) % 16);
            break;
        }

        case '-':
        {

            int a = values.get();
            values.pop();

            int b = values.get();
            values.pop();

            values.push((b - a + 16) % 16);
            break;
        }
        case ':':
            values.push(values.get());
            break;
        case '%':
        {
            int a = values.get();
            values.pop();

            int b = values.get();
            values.pop();

            values.push(a);
            values.push(b);
            break;
        }
        case '"':
            printMode = !printMode;
            break;
        case '$':
            values.pop();
            break;
        case '.':
            std::cout << "0123456789ABCDEF"[values.get()];
            break;
        case '#':
        {
            char cInput;

            if (inputFile.get(cInput))
            {
                if (cInput >= '0' && cInput <= '9')
                    values.push(cInput - '0');
                else if (cInput >= 'A' && cInput <= 'F')
                    values.push(cInput - 'A' + 10);
                else
                {
                    std::cerr << "Invalid hex input\n";
                    return 1;
                }
            }
            else
            {
                values.push(0);
            }
            break;
        }
        case '{':
            ret = pointer;
            break;

        case '}':
        {
            int direction = pointer.direction;
            pointer = ret;
            pointer.direction = direction;
            continue;
        }
        case '&':
        {
            char charInput;

            if (!inputFile.get(charInput))
                charInput = 0;

            unsigned char byte = static_cast<unsigned char>(charInput);

            values.push((byte >> 4) & 0xF);
            values.push(byte & 0xF);
            break;
        }
        case ',':
        {
            int low = values.get();
            values.pop();

            int high = values.get();
            values.pop();

            char cOut = static_cast<char>((high << 4) | low);
            std::cout << cOut;
            break;
        }
        case 'n':
            std::cout << '\n';
            break;
        case '^':
        {
            Pointer branch = {
                pointer.row + 1,
                pointer.col + 1,
                1};

            branches.push(branch);
            pointer.direction = -1;
            break;
        }
        case '*':
            break;
        case '/':
            pointer.direction = -1;
            break;
        case '\\':
            pointer.direction = 1;
            break;
        case '~':
            if (!branches.empty())
            {
                pointer = branches.get();
                branches.pop();
            }
            else
            {
                return 0;
            }
            continue;
        case '?':
        {
            int value = values.get();

            if (value == 0)
            {
                pointer.direction = -1;
            }
            else
            {
                values.pop();
                values.push(value - 1);
                pointer.direction = 1;
            }

            break;
        }
        default:
            break;
        }
        movePointer(pointer);
    }
}