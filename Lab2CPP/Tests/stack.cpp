#include <iostream>
#include "stack.h"
#include <unordered_map>

int main()
{
    std::string s = "({[]})";

    Stack st;
    std::unordered_map<char, char> pairs = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };
    
    bool isValid = false;

    for (char c : s)
    {
        if (c == '(' || c == '[' || c == '{')
        { 
            st.push(std::string(1, c)); 
        } 
        else if (c == ')' || c == ']' || c == '}') 
        { 
            if (st.empty() || st.get()[0] != pairs[c])
            { 
                isValid = false; 
                break;
            }
            st.pop(); 
        }
    }

    if (st.empty()) 
    {
        isValid = true;
    } 
  
    
    if (!isValid)
    {
        std::cout << "stack error";
        return 1;
    } 
}
