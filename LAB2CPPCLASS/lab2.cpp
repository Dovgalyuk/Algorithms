#include <iostream>
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

        if (validReg(value[0]) && value.size() == 1)
        {
            cmd.value = value[0];
        }
        else
        {
            cmd.value = stoi(value);
        }
    }
    else if (op == "pop")
    {
        cmd.type = typeCommand::POP;
        string reg;

        iss >> reg;
        cmd.value = reg[0];
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

        switch (cmd.type)
        {
            case typeCommand::PUSH: 
            {
                if (validReg(static_cast<char>(cmd.value)))
                {
                    processorStack.push(registers[static_cast<char>(cmd.value)]);
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
                    cout << "BAD POP" << endl;
                    inputFile.close();
                    processorStack.~Stack();
                    return 1;
                }

                int value = processorStack.get();
                if (value == CALL_MARKER || !validReg(static_cast<char>(cmd.value))) 
                {
                    cout << "BAD POP" << endl;
                    inputFile.close();
                    processorStack.~Stack();
                    return 1;
                }

                registers[static_cast<char>(cmd.value)] = value;
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
                    cout << "BAD RET" << endl;
                    inputFile.close();
                    processorStack.~Stack();
                    return 1;
                }
                processorStack.pop();
                break;
            }
            case typeCommand::INVALID: 
            {
                cout << "Invalid command!" << endl;
                inputFile.close();
                processorStack.~Stack();
                return 1;
            }
            default:
                break;
        }
    }

    for (const auto& reg : registers) 
    {
        cout << reg.first << " = " << reg.second << endl;
    }

    return 0;
}