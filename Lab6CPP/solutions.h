#include <string>
#include <vector>

struct Ans{
    bool is_number;
    std::string expression;
    int value;
};

Ans solve1(std::vector<int> &numbers, std::vector<char> &operations);
Ans solve2(std::vector<int> &numbers, std::vector<char> &operations);