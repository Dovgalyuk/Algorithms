#include "lab2.h"
#include "list.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

static std::vector<std::string> COMMANDS_WITH_VARS = {"bipush", "iload", "istore"};
static std::vector<std::string> COMMANDS_ARITHMETIC = {"imul", "iand", "ior", "ixor", "iadd", "isub"};

std::vector<std::string> JavaMachineData::toResult()
{
    std::vector<std::string> result;
    result.push_back("stack:");
    while (!stack.empty())
    {
        result.push_back(std::to_string(stack.get()));
        stack.pop();
    }
    result.push_back("vars:");
    for (auto const &var : variables)
    {
        result.push_back(std::to_string(var));
    }
    return result;
}

void operationArithmetic(JavaMachineData &data, std::string command)
{
    auto v1 = data.stack.get();
    data.stack.pop();
    auto v2 = data.stack.get();
    data.stack.pop();
    Data result;
    if (command == "imul")
    {
        result = v1 * v2;
    }
    else if (command == "isub")
    {
        result = v1 - v2;
    }
    else if (command == "iand")
    {
        result = v1 & v2;
    }
    else if (command == "ior")
    {
        result = v1 | v2;
    }
    else if (command == "ixor")
    {
        result = v1 ^ v2;
    }
    else if (command == "iadd")
    {
        result = v1 + v2;
    }
    else
    {
        throw std::logic_error("There is no handler for arithmetic command: " + command);
    }
    data.stack.push(result);
}
void handleLine(JavaMachineData &data, std::string line)
{
    std::replace(line.begin(), line.end(), '_', ' ');
    std::stringstream ss;
    ss << line;
    std::string command;
    Data var;
    ss >> command;
    if (std::find(COMMANDS_WITH_VARS.begin(), COMMANDS_WITH_VARS.end(), command) != COMMANDS_WITH_VARS.end())
    {
        ss >> var;
    }
    if (std::find(COMMANDS_ARITHMETIC.begin(), COMMANDS_ARITHMETIC.end(), command) != COMMANDS_ARITHMETIC.end())
    {
        operationArithmetic(data, command);
    }
    else if (command == "bipush")
    {
        data.stack.push(var);
    }
    else if (command == "pop")
    {
        data.stack.pop();
    }
    else if (command == "istore")
    {
        auto v = data.stack.get();
        data.stack.pop();
        data.variables[var] = v;
    }
    else if (command == "iload")
    {
        auto v = data.variables[var];
        data.stack.push(v);
    }
    else if (command == "swap")
    {
        auto v1 = data.stack.get();
        data.stack.pop();
        auto v2 = data.stack.get();
        data.stack.pop();
        data.stack.push(v1);
        data.stack.push(v2);
    }
    else
    {
        throw std::runtime_error("Unknown command: " + command);
    }
}
std::vector<std::string> JAVAMachine(std::ifstream &input)
{
    std::string line;
    JavaMachineData data;

    while (!input.eof())
    {
        std::getline(input, line);
        handleLine(data, line);
    }

    return data.toResult();
}
