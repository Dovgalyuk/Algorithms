#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"
bool task1(const std::string &checkString)
{
    List<char> firstSymbols = {'\'', '\"', '(', '[', '{'};
    List<char> secondSymbols = {'\'', '\"', ')', ']', '}'};
    
    Stack<char> c;
    for (auto i : checkString)
    {
        if (!c.empty() && secondSymbols.contains(i) && firstSymbols.indexOf(c.get()) == secondSymbols.indexOf(i))
            c.pop();
        else if (firstSymbols.contains(i))
            c.push(i);
        else if (c.empty() && secondSymbols.contains(i))
        {
            c.push(i);
            break;
        }
    }
    if (c.empty())
        return true
    else
        return false
}

int main()
{
    std::ifstream infile("input.txt");
    std::ofstream outfile("output.txt"); 
    std::string s;

    std::getline(infile, s);
    if (task1(s)) {
        outfile << "YES" << std::endl; 
    }
    else {
        outfile << "NO" << std::endl; 
    }
    return 0;
}