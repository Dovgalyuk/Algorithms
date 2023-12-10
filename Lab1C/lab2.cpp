#include "stack.h"
#include "stack.cpp"
#include <iostream>
#include <map>
#include <string> 
#include <algorithm> 

bool isCorrect(std::string& s) {
    
    s.erase(std::remove_if(s.begin(), s.end(), [](char c) {
        return c != '(' && c != ')' && c != '[' && c != ']' && c != '{' && c != '}' && c != '"';
        }), s.end());
    //штука для того, чтобы проверять не просто строку из скобок каких-то
    //но и чтобы мочь проверить, например, закрытие скобок в ветвлении или цикле for, или простом тексте

    Stack stack;
    Stack qStack;
    std::map<char, char> pairs = {
        {')', '('},
        {']', '['},
        {'}', '{'},
        {'"', '"'}
    };

    for (char c : s) {
        if (!qStack.empty()) {
            if (c == '"') {
                qStack.pop();
            }
        }
        else {
            if (c == '"') {
                qStack.push(c);
            }
            else if (pairs.find(c) == pairs.end()) {
                stack.push(c);
            }
            else {
                if (stack.empty() || stack.get() != pairs[c])
                    return false;
                stack.pop();
            }
        }
    }
    //Код будет работать с любыми вариантами, включая варианты, когда внутри кавычек находятся не закрытые скобки
    //То,что внутри кавычек, будет рассматриваться, как текст. Иными словами, код выдаст true на {"[]]"}

    if (stack.empty()) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    std::string s;
    std::getline(std::cin, s);

    if (isCorrect(s))
        std::cout << "YES";
    else
        std::cout << "NO";

    return 0;
}
