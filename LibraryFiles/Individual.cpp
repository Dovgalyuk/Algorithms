#include <iostream>
#include "array.h"
#include "stack.h"
#include <vector>
#include <algorithm>


size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}

void do_operation(StackByList<char>& operations, StackByList<double>& numbers){
    if (numbers.size() < 2){
        std::cerr << "UNDERFLOW" << std::endl;
        exit(1);
    }
    switch (operations.top()) {
        case '+': {
            double first = numbers.top();
            numbers.pop();
            double second = numbers.top();
            numbers.pop();
            numbers.push(first + second);
            break;
        }
        case '-': {
            double first = numbers.top();
            numbers.pop();
            double second = numbers.top();
            numbers.pop();
            numbers.push(first - second);
            break;
        }
        case '*': {
            double first = numbers.top();
            numbers.pop();
            double second = numbers.top();
            numbers.pop();
            numbers.push(first * second);
            break;
        }
        case '/': {
            double first = numbers.top();
            numbers.pop();
            double second = numbers.top();
            numbers.pop();
            if (second == 0){
                std::cerr << "ZERO" << std::endl;
                exit(1);
            }
            numbers.push(first / second);
            break;
        }
        default: {
            std::cout << "unknown operation" << std::endl;
            exit(1);
        }
    }
    operations.pop();
}

void lab2(){
    StackByList<char> operations;
    StackByList<double> numbers;

    std::string input;
    getline(std::cin, input);

    std::vector<std::string> buffer;

    split(input, buffer, ' ');
    for(const auto& str : buffer){
        if (str.length() == 1 && (str[0] == '-' || str[0] == '+' || str[0] == '*' || str[0] == '/')){
            operations.push(str[0]);
        } else {
            try{
                double value = std::stod(str);
                numbers.push(value);
            }
            catch(std::exception& e){
                std::cerr << e.what() << std::endl;
            }
        }
    }

    while (operations.size() > 0) {
        do_operation(operations, numbers);
    }

    if (numbers.size() > 1) {
        std::cerr << "OVERFLOW" << std::endl;
        exit(1);
    }
    std::cout << "result = " << numbers.top() << std::endl;
    numbers.pop();

}


int main() {
    lab2();
}
