#include "stack.h"
#include "stack.cpp"
#include <iostream>
#include <map>
#include <string> 
#include <algorithm> 
#include <deque>

void addStack(std::deque<std::pair<Stack, int>>& vect,int& level,int value) {
    try {
        Stack st = vect.at(level).first;
    }
    catch (std::out_of_range& e) {
        Stack newStack;
        vect.push_back(std::make_pair(newStack, value));      
    }
}
bool isCorrect(std::string& s) {
    size_t pos = 0;
    std::string substr = "\\\"";
    while ((pos = s.find(substr, pos)) != std::string::npos) {
        s.erase(pos, substr.length());
    }
    
    s.erase(std::remove_if(s.begin(), s.end(), [](char c) {
        return c != '(' && c != ')' && c != '[' && c != ']' && c != '{' && c != '}' && c != '"' && c!= '\'';
        }), s.end());
    std::cout << s << std::endl;
    //штука для того, чтобы проверять не просто строку из скобок каких-то
    //но и чтобы мочь проверить, например, закрытие скобок в ветвлении или цикле for, или простом тексте

    Stack stack;
    int value = 0;//пусть 0-скобки, 1-", 2-' 
    std::deque<std::pair<Stack,int>> vect;
    std::map<char, char> pairs = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };
    vect.push_back(std::make_pair(stack, value));
    int level = 0;
    bool inQ = false;
    bool inSQ = false;

    for (char c : s) {
        if (inQ == true) {
            if (!vect.at(level).first.empty()) { //Код поддерживает вложенность кавычек, кстати))
                if (c == '"') {                 //Для этого стоит чередовать " и '
                    vect.at(level).first.pop();//Как-то так, ёмоё.
                    level--;
                    if (vect.at(level).second == 2) {
                        inSQ = true;
                    }
                    inQ = false;
                }
                else if (c == '\'') {
                    inSQ = true;
                    inQ = false;
                    level++;
                    addStack(vect, level,2);
                    vect.at(level).first.push(c);
                }
                else if (pairs.find(c) == pairs.end()) {
                    vect.at(level).first.push(c);
                }
                else {
                    if (vect.at(level).first.empty() || vect.at(level).first.get() != pairs[c]) {
                        return false;
                    }
                    vect.at(level).first.pop();
                }
            }
        }
        else if(inSQ == true) {
            if (!vect.at(level).first.empty()) {
                if (c == '\'') {
                    vect.at(level).first.pop();
                    level--;
                    inSQ = false;
                    if (vect.at(level).second == 1) {
                        inQ = true;
                    }
                }
                else if (c == '"') {
                    inQ = true;
                    inSQ = false;
                    level++;
                    addStack(vect, level,1);
                    vect.at(level).first.push(c);
                }
                else if (pairs.find(c) == pairs.end()) {
                    vect.at(level).first.push(c);
                }
                else {
                    if (vect.at(level).first.empty() || vect.at(level).first.get() != pairs[c]) {
                        return false;
                    }
                    vect.at(level).first.pop();
                }
            }
        }
        else {
            if (c == '"') {
                level++;
                addStack(vect, level,1);
                inQ = true;
                vect.at(level).first.push(c);
            }
            else if (c == '\'') {
                level++;
                addStack(vect, level,2);
                inSQ = true;
                vect.at(level).first.push(c);
            }
            else if (pairs.find(c) == pairs.end()) {
                vect.at(level).first.push(c);
            }
            else {
                if (vect.at(level).first.empty() || vect.at(level).first.get() != pairs[c]) {
                    return false;
                }
                vect.at(level).first.pop();
            }
        }
    }
    
    for (int num=0; num < vect.size();num++) {
        if (!vect.at(num).first.empty()) {
            return false;
        }
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
