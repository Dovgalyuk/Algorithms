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

int main(int argc, char* argv[])
{
    
    return 0;
}