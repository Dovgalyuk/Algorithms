#include "stack.h"
#include <iostream>
#include <string>



std::string getPart(Stack<char>* exp) {
    std::string part = "";
    do {
        part.push_back(exp->get());
        exp->pop();
        if (exp->empty()) {
            return part;
        }
    } while ((exp->get() != '+') && 
            (exp->get() != '-'));
    return part;
}

char checkFirstAction(std::string exp) {
    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == '*') 
            return '*';
        if (exp[i] == '/') 
            return '/';
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

int calculate(std::string exp) {
    int result = 0;
    char action = checkFirstAction(exp);
    if (action == ' ') {
        return std::stoi(getFirstNumber(exp));
    } else {
        int t = std::stoi(getFirstNumber(exp));
        exp = exp.substr(getFirstNumber(exp).length() + 1, exp.length() - getFirstNumber(exp).length() - 1);
        result = calc(t, action, calculate(exp));
        return result;
    }


    


}

int main() {
    //reading string
    std::cout << "input: ";
    std::string str;
    std::getline(std::cin, str);
    str = "+" + str;
    // example: "+1+2*3-1*2-4"

    //string -> Stack<char>
    Stack<char> * expression = new Stack<char>;
    for (int i= str.length()-1; i>=0; i--) {
        expression->push(str[i]);
    }

    //split expression into parts
    Stack<std::string> * parts = new Stack<std::string>;
    while (!expression->empty()) {
        parts->push(getPart(expression));
    }
    delete expression;
    // example: (+1+2*3-1*2-4) -> {"-4","-1*2","+2*3","+1"}

    //calculate every part, add them to result
    int result = 0;
    while (!parts->empty()) {
        std::string part = parts->get();
        parts->pop();
        int k = 1;
        if (part.front() == '-') {
            k = -1;
        }
        part = part.substr(1, part.length() - 1);
        result += k * calculate(part);
        
    }
    delete parts;


    std::cout << "output: " << result <<"\n";
    return 0;
}