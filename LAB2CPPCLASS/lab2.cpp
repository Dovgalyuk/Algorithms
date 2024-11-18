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
        
    }
    else if (op == "pop")
    {
        
    }
    else if (op == "call")
    {
        
    }
    else if (op == "ret")
    {
        
    }

    return cmd;
}

int main(int argc, char* argv[])
{
    
    return 0;
}