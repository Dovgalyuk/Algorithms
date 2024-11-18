#include "lab3.h"
#include <fstream>
#include <iostream>
#include <string>

bool check_result(int test_num, std::ifstream &input, std::ifstream &output)
{
    auto res = Task(input);
    std::string line;
    size_t lineNum = 0;
    while (!output.eof())
    {
        std::getline(output, line);
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
        if (lineNum >= res.size())
        {
            std::cout << "TEST FAIL: lineNum(" << lineNum << ") >= res.size()(" << res.size() << ")" << std::endl;
            return false;
        }
        if (res.at(lineNum) != line)
        {
            std::cout << "TEST FAIL at line num = " << lineNum << ": expected = " << line
                      << "\nresult = " << res.at(lineNum) << std::endl;
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
        input = std::ifstream("/Users/user/Projects/Algorithms/Lab3CPP/input_test_tasks.txt");
        output = std::ifstream("/Users/user/Projects/Algorithms/Lab3CPP/output_test_tasks.txt");
    }
    else
    {
        input = std::ifstream(argv[1]);
        output = std::ifstream(argv[2]);
    }
    
    if (!check_result(1, input, output))
    {
        std::cout << "TEST 1 FAILED";
        return -2;
    }
    else
    {
        return 0;
    }
}