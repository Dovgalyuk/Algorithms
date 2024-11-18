#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <map>
#include "stack.h"

using namespace std;

enum class typeCommand { PUSH, POP, CALL, RET, INVALID };

struct command 
{
    typeCommand type;
    size_t value;
};

bool valid(char reg) { return reg >= 'A' && reg <= 'D'; }

command parse(const string& input)
{
    command cmd = { typeCommand::INVALID, 0 };
    istringstream iss(input);
    string op;

    iss >> op;

    if (op == "push")
    {
        cmd.type = typeCommand::PUSH;
        
        iss >> cmd.value;
    }
    else if (op == "pop")
    {
        cmd.type = typeCommand::POP;
        std::string reg;

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
    
    return 0;
}