#include "stack.h"
#include <iostream>
#include <map>
#include <string> 
#include <algorithm> 
#include <deque>

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
    int level=0;
    bool inQ = false; 
    bool inSQ = false;
    for (char c : s) {
        if (inQ) {
            if (c == '"') {
                if (stack.empty() || stack.get() != '"') {
                    return false;
                }
                stack.pop();
                inQ = false;
                if (level > 1) {
                    inSQ = true;
                }
                level--;
            }
            else if (c == '\'') {
                stack.push(c);
                inQ = false;
                inSQ = true;
                level++;
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
        else if (inSQ) {
            if (c == '\'') {
                if (stack.empty() || stack.get() != '\'') {
                    return false;
                }
                stack.pop();
                inSQ = false;
                if (level > 1) {
                    inQ = true;
                }
                level--;
            }
            else if (c == '"') {
                stack.push(c);
                inQ = true;
                inSQ = false;
                level++;
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
        else {
            if (c == '"' || c == '\'') {
                stack.push(c);
                inQ = (c == '"');
                inSQ = (c == '\'');
                level++;
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
    }

    if (!stack.empty()) {
        return false;
    }

    return true;
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
