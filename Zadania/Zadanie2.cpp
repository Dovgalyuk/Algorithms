#include "stack.h"
#include <iostream>
#include <string>

char checkFirstAction(std::string exp) {
    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == '*') 
            return '*';
        if (exp[i] == '/') 
            return '/';
        if (exp[i] == '+') 
            return '+';
        if (exp[i] == '-') 
            return '-';
    }
    return ' ';
}

std::string getFirstNumber(std::string exp) {
    std::string number;
    for (int i = 0; i < exp.length(); i++) {
        if (std::isdigit(exp[i])) {
            number.push_back(exp[i]);
        }
        else {
            return number;
        }
    }
    return number;
}

int calc(int a, char action, int b) {
    if (action == '*')
    return a*b;
    if (action == '/')
    return a/b;
}

int main() {
    
    std::cout << "input: ";
    std::string str;
    std::getline(std::cin, str);
    
    Stack<int> * stack = new Stack<int>;
    stack->push(std::stoi(getFirstNumber(str)));
    str.erase(0, getFirstNumber(str).length());
    while (!str.empty()) {
        char nextAction = checkFirstAction(str);
        str.erase(0,1);
        if ((nextAction == '+') || (nextAction == '-')) {
            int k = 1;
            if (nextAction == '-') {
                k = -1;
            }
            stack->push(k * std::stoi(getFirstNumber(str)));
        } else {
            int t = stack->get();
            stack->pop();
            stack->push(calc(t, nextAction, std::stoi(getFirstNumber(str))));
        }
        str.erase(0, getFirstNumber(str).length());
    } 
    int result = 0;
    while (!stack->empty()) {
        result += stack->get();
        stack->pop();
    }
   delete stack;
   std::cout << "output: " << result;
}