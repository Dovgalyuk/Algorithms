#include "stack.h"
#include <fstream>
#include <vector>

static std::vector<std::string> COMMANDS_WITH_VARS = {"bipush", "iload", "istore"};
static std::vector<std::string> COMMANDS_ARITHMETIC = {"imul", "iand", "ior", "ixor", "iadd", "isub"};

struct JavaMachineData
{
    Stack stack;
    std::array<Data, 4> variables = {0, 0, 0, 0};
    std::vector<std::string> toResult();
};
void operationArithmetic(JavaMachineData &data, std::string command);
void handleLine(JavaMachineData &data, std::string line);
std::vector<std::string> JAVAMachine(std::ifstream &input);