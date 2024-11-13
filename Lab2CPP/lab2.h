#include "stack.h"
#include <array>
#include <vector>
#include <string>
#include <fstream>

struct JavaMachineData
{
    Stack stack;
    std::array<Data, 4> variables = {0, 0, 0, 0};
    std::vector<std::string> toResult();
};
void operationArithmetic(JavaMachineData &data, std::string command);
void handleLine(JavaMachineData &data, std::string line);
std::vector<std::string> JAVAMachine(std::ifstream &input);