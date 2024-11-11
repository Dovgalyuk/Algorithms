#include "lab2.h"
#include <fstream>
#include <string>

bool check_result(int test_num, std::ifstream &input, std::ifstream &output)
{
    auto res = JAVAMachine(input);
    std::string line;
    size_t lineNum = 0;
    while (!output.eof())
    {
        std::getline(output, line);
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
        if (lineNum >= res.size())
        {
            return false;
        }
        if (res.at(lineNum) != line)
        {
            return false;
        }
        lineNum++;
    }
    return true;
}
int main(int argc, char **argv)
{
    std::ifstream input;
    std::ifstream output;
    if (argc <= 2)
    {
        return -1;
    }
    else
    {
        input = std::ifstream(argv[1]);
        output = std::ifstream(argv[2]);
    }
    if (!check_result(1, input, output))
    {
        return -2;
    }
    else
    {
        return 0;
    }
}