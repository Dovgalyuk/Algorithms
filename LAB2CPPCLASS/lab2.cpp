#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "stack.h"

using namespace std;

enum class typeCommand { PUSH, POP, CALL, RET, INVALID };

struct command 
{
    typeCommand type;
    size_t value;
};

bool validReg(char reg) { return reg >= 'A' && reg <= 'D'; }

command parse(const string& input)
{
    command cmd = { typeCommand::INVALID, 0 };
    istringstream iss(input);
    string op;

    iss >> op;

    if (op == "push")
    {
        cmd.type = typeCommand::PUSH;
        string value;
        iss >> value;

        if (value.empty())
        {
            cmd.type = typeCommand::INVALID;
        }
        else if (validReg(value[0]) && value.size() == 1)
        {
            cmd.value = value[0];
        }
        else if (all_of(value.begin(), value.end(), ::isdigit))
        {
            try
            {
                cmd.value = stoi(value);
            }
            catch (const exception&)
            {
                cmd.type = typeCommand::INVALID;
            }
        }
        else
        {
            cmd.type = typeCommand::INVALID;
        }
    }
    else if (op == "pop")
    {
        cmd.type = typeCommand::POP;
        string reg;

        iss >> reg;
        if (reg.size() == 1 && validReg(reg[0]))
        {
            cmd.value = reg[0] - 'A';
        }
        else
        {
            cmd.type = typeCommand::INVALID;
        }
    }
    else if (op == "call")
    {
        cmd.type = typeCommand::CALL;
    }
    else if (op == "ret")
    {
        cmd.type = typeCommand::RET;    
    }

    return cmd;
}

int main(int argc, char* argv[])
{
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) 
    {
        cerr << "Error opening input file" << endl;
        return 1;
    }

    Stack processorStack;

    unordered_map<char, size_t> registers = { {'A', 0}, {'B', 0}, {'C', 0}, {'D', 0} };
    const int CALL_MARKER = static_cast<int>(-1);

    string input;

    while (getline(inputFile, input))
    {
        command cmd = parse(input);

        if (cmd.type == typeCommand::INVALID)
        {
            cout << "Invalid command!" << endl;
            inputFile.close();
            processorStack.~Stack();
            return 1;
        }

        switch (cmd.type)
        {
            case typeCommand::PUSH: 
            {
                if (cmd.value >= 0 && cmd.value <= 3)
                {
                    processorStack.push(registers['A' + cmd.value]);
                }
                else
                {
                    processorStack.push(cmd.value);
                }
                break;
            }
            case typeCommand::POP: 
            {
                if (processorStack.empty()) 
                {
                    cout << "BAD POP: Stack is empty" << endl;
                    inputFile.close();
                    processorStack.~Stack();
                    return 1;
                }

                int value = processorStack.get();
                if (value == CALL_MARKER || cmd.value < 0 || cmd.value > 3) 
                {
                    cout << "BAD POP: Invalid value or register" << endl;
                    inputFile.close();
                    processorStack.~Stack();
                    return 1;
                }

                registers['A' + cmd.value] = value;
                processorStack.pop();
                break;
            }
            case typeCommand::CALL: 
            {
                processorStack.push(CALL_MARKER);
                break;
            }
            case typeCommand::RET: 
            {
                if (processorStack.empty() || processorStack.get() != CALL_MARKER) 
                {
                    cout << "BAD RET: No CALL marker on stack" << endl;
                    inputFile.close();
                    processorStack.~Stack();
                    return 1;
                }
                processorStack.pop();
                break;
            }
            default:
                cerr << "Unknown error occurred!" << endl;
                inputFile.close();
                processorStack.~Stack();
                return 1;
        }
    }

    for (const auto& reg : registers) 
    {
        cout << reg.first << " = " << reg.second << endl;
    }

    return 0;
}