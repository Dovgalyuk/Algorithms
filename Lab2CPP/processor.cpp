
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "stack.h"

using namespace std;

struct Instruction
{
    string command;
    string argument;
};

int getRegisterIndex(const string& name)
{
    if (name == "A") return 0;
    if (name == "B") return 1;
    if (name == "C") return 2;
    if (name == "D") return 3;

    return -1;
}

// Находим ret, который соответствует текущему call.
int findMatchingRet(const vector<Instruction>& program, int callIndex)
{
    int nestedCalls = 0;

    for (int i = callIndex + 1; i < static_cast<int>(program.size()); i++)
    {
        if (program[i].command == "call")
        {
            nestedCalls++;
        }
        else if (program[i].command == "ret")
        {
            if (nestedCalls == 0)
            {
                return i;
            }

            nestedCalls--;
        }
    }

    return -1;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    ifstream file(argv[1]);

    if (!file.is_open())
    {
        return 1;
    }

    vector<Instruction> program;

    string line;

    while (getline(file, line))
    {
        stringstream stream(line);

        Instruction instruction;

        stream >> instruction.command;
        stream >> instruction.argument;

        if (!instruction.command.empty())
        {
            program.push_back(instruction);
        }
    }

    file.close();

    int registers[4] = {0, 0, 0, 0};

    Stack* values = stack_create();
    Stack* types = stack_create();

    auto cleanup = [&]()
    {
        stack_delete(values);
        stack_delete(types);
    };

    int ip = 0;

    while (ip < static_cast<int>(program.size()))
    {
        Instruction instruction = program[ip];

        if (instruction.command == "push")
        {
            int value;

            stringstream stream(instruction.argument);

            if (stream >> value)
            {
                string extra;

                if (stream >> extra)
                {
                    cout << "BAD PUSH" << endl;
                    cleanup();
                    return 1;
                }

                stack_push(values, value);
                stack_push(types, 0);
            }
            else
            {
                int index = getRegisterIndex(instruction.argument);

                if (index == -1)
                {
                    cout << "BAD PUSH" << endl;
                    cleanup();
                    return 1;
                }

                stack_push(values, registers[index]);
                stack_push(types, 0);
            }
        }
        else if (instruction.command == "pop")
        {
            if (stack_empty(values) || stack_get(types) == 1)
            {
                cout << "BAD POP" << endl;
                cleanup();
                return 1;
            }

            int index = getRegisterIndex(instruction.argument);

            if (index == -1)
            {
                cout << "BAD POP" << endl;
                cleanup();
                return 1;
            }

            registers[index] = stack_get(values);

            stack_pop(values);
            stack_pop(types);
        }
        else if (instruction.command == "add" || instruction.command == "sub" || instruction.command == "mul")
        {
            if (stack_empty(values) || stack_get(types) == 1)
            {
                cout << "BAD OPERATION" << endl;
                cleanup();
                return 1;
            }

            int first = stack_get(values);

            stack_pop(values);
            stack_pop(types);

            if (stack_empty(values) || stack_get(types) == 1)
            {
                cout << "BAD OPERATION" << endl;
                cleanup();
                return 1;
            }

            int second = stack_get(values);

            stack_pop(values);
            stack_pop(types);

            int result = 0;

            if (instruction.command == "add")
            {
                result = second + first;
            }
            else if (instruction.command == "sub")
            {
                result = second - first;
            }
            else if (instruction.command == "mul")
            {
                result = second * first;
            }

            stack_push(values, result);
            stack_push(types, 0);
        }
        else if (instruction.command == "call")
        {
            int returnAddress = findMatchingRet(program, ip);

            if (returnAddress == -1)
            {
                cout << "BAD CALL" << endl;
                cleanup();
                return 1;
            }

            stack_push(values, returnAddress + 1);
            stack_push(types, 1);

            ip++;
            continue;
        }
        else if (instruction.command == "ret")
        {
            if (stack_empty(values) || stack_get(types) == 0)
            {
                cout << "BAD RET" << endl;
                cleanup();
                return 1;
            }

            // Возвращаемся к сохранённой инструкции.
            ip = stack_get(values);

            stack_pop(values);
            stack_pop(types);

            continue;
        }
        else
        {
            cout << "BAD COMMAND" << endl;
            cleanup();
            return 1;
        }

        ip++;
    }

    cout << "A = " << registers[0] << endl;
    cout << "B = " << registers[1] << endl;
    cout << "C = " << registers[2] << endl;
    cout << "D = " << registers[3] << endl;

    cleanup();

    return 0;
}
