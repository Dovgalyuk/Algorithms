#include "stack.h"
#include <iostream>
#include <map>
#include <string> 
#include <algorithm> 

bool isCorrect(std::string& s) {
    size_t pos = 0;
    std::string substr = "\\\"";
    while ((pos = s.find(substr, pos)) != std::string::npos) {
        s.erase(pos, substr.length());
    }

    s.erase(std::remove_if(s.begin(), s.end(), [](char c) {
        return c != '(' && c != ')' && c != '[' && c != ']' && c != '{' && c != '}' && c != '"' && c != '\'';
        }), s.end());

    std::cout << s << std::endl;

    Stack stack;
    std::map<char, char> pairs = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };

    for (char c : s) {
        if (c == '"' || c == '\'') {
            if (!stack.empty() && stack.get() == c) {
                stack.pop();
            }
            else {
                stack.push(c);
            }
        }
        else if (pairs.find(c) == pairs.end()) {
            stack.push(c);
        }
        else {
            if (stack.empty() || stack.get() != pairs[c]) {
                return false;
            }
            stack.pop();
        }
    }

    return stack.empty();
}

int main() {
    setlocale(0, "Russian");
    std::string s ;
    std::getline(std::cin, s);
    
    if (isCorrect(s))
        std::cout << "YES";
    else
        std::cout << "NO";

    return 0;
}
