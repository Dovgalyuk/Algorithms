#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "stack.h"

using namespace std;

enum CellType
{
    NUMBER,
    RETURN_ADDRESS
};

struct StackCell
{
    CellType type;
    int value;
};

int getRegisterIndex(const string &name)
{
    if (name == "A")
        return 0;
    if (name == "B")
        return 1;
    if (name == "C")
        return 2;
    if (name == "D")
        return 3;

    return -1;
}

bool getNumber(const string &text, int &number)
{
    stringstream input(text);
    input >> number;

    return !input.fail() && input.eof();
}

bool takeNumber(Stack<StackCell> &stack, int &number)
{
    if (stack.empty())
        return false;

    StackCell cell = stack.get();
    if (cell.type != NUMBER)
        return false;

    number = cell.value;
    stack.pop();
    return true;
}

void pushNumber(Stack<StackCell> &stack, int number)
{
    StackCell cell;
    cell.type = NUMBER;
    cell.value = number;
    stack.push(cell);
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;

    ifstream input(argv[1]);
    if (!input)
        return 1;

    Stack<StackCell> stack;
    int registers[4] = {0, 0, 0, 0};
    int lineNumber = 0;
    string line;

    while (getline(input, line))
    {
        lineNumber++;

        stringstream lineInput(line);
        string command;
        lineInput >> command;

        if (command.empty())
            continue;

        if (command == "push")
        {
            string argument;
            lineInput >> argument;

            int registerIndex = getRegisterIndex(argument);
            int number = 0;

            if (registerIndex != -1)
            {
                number = registers[registerIndex];
            }
            else if (!getNumber(argument, number))
            {
                cout << "BAD PUSH\n";
                return 0;
            }

            pushNumber(stack, number);
        }
        else if (command == "pop")
        {
            string registerName;
            lineInput >> registerName;

            int registerIndex = getRegisterIndex(registerName);
            int number = 0;

            if (registerIndex == -1 || !takeNumber(stack, number))
            {
                cout << "BAD POP\n";
                return 0;
            }

            registers[registerIndex] = number;
        }
        else if (command == "add" || command == "sub" || command == "mul")
        {
            int right = 0;
            int left = 0;

            if (!takeNumber(stack, right) || !takeNumber(stack, left))
            {
                cout << "BAD " << command << "\n";
                return 0;
            }

            int result = 0;

            if (command == "add")
                result = left + right;
            else if (command == "sub")
                result = left - right;
            else
                result = left * right;

            pushNumber(stack, result);
        }
        else if (command == "call")
        {
            StackCell cell;
            cell.type = RETURN_ADDRESS;
            cell.value = lineNumber + 1;
            stack.push(cell);
        }
        else if (command == "ret")
        {
            if (stack.empty() || stack.get().type != RETURN_ADDRESS)
            {
                cout << "BAD RET\n";
                return 0;
            }

            stack.pop();
        }
        else
        {
            cout << "BAD COMMAND\n";
            return 0;
        }
    }

    cout << "A = " << registers[0] << "\n";
    cout << "B = " << registers[1] << "\n";
    cout << "C = " << registers[2] << "\n";
    cout << "D = " << registers[3] << "\n";

    return 0;
}
