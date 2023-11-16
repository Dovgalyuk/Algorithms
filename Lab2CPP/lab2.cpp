#include <iostream>
#include "stack.h"

void task1(const std::string &checkString)
{
    List<char> openSymbols = {'\'', '\"', '('};
    List<char> closeSymbols = {'\'', '\"', ')'};

    Stack<char> st;
    for (auto i : checkString)
    {
        if (!st.empty() && closeSymbols.contains(i) && openSymbols.indexOf(st.get()) == closeSymbols.indexOf(i))
            st.pop();
        else if (openSymbols.contains(i))
            st.push(i);
    }
    if (st.empty())
        std::cout << "YES" << std::endl;
    else
        std::cout << "NO" << std::endl;
}

void task2(List<int> &list)
{
}

int main()
{
    std::string testPass = "124faffdsfdsfsdffdsfds'dfsfdsfwe\"fdsfds\"'";
    std::string testFail = "12srefwewefwedsdffwefwefe\"sdfds\"dsff'sdffds''";
    task1(testPass);
    task1(testFail);
    return 0;
}
