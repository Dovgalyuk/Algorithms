#include <iostream>
#include <cctype>
#include <vector>
#include "../LibraryCPPTemplate/stack.h"

void calculate(const std::string& input);
std::vector<std::string> *calculateOrder(const std::string& input);
int getOperationPriority(char ch);

int main() {
    std::string input;
    std::cout << "Input calculation string:" << std::endl;
    std::cin >> input;
    calculate(input);
    return 0;
}

void calculate(const std::string& input) {
    std::vector<std::string> *inputVector = calculateOrder(input);
    Stack<double> numbers;

    for (auto str : *inputVector) {
        if (str.find_first_not_of("0123456789") == std::string::npos) {
            numbers.push(std::stoi(str));
            continue;
        }
        const char ch = str.at(0);
        double first, second, result;
        second = numbers.get();
        numbers.pop();
        first = numbers.get();
        numbers.pop();
        switch (ch) {
            case '-':
                result = first - second;
                break;
            case '+':
                result = first + second;
                break;
            case '/':
                result = first / second;
                break;
            case '*':
                result = first * second;
                break;
            default:
                std::cout << "String have unknown operation" << std::endl;
                exit(-1);
        }
        numbers.push(result);
    }
    std::cout << "Calculation result: "<< numbers.get() << std::endl;
}

std::vector<std::string> *calculateOrder(const std::string& input) {
    Stack<std::string> operationStack;

    std::string number;
    auto *result = new std::vector<std::string>;

    for (char ch : input) {
        if (isdigit(ch)) {
            number.push_back(ch);
            continue;
        }
        if (!number.empty()) {
            result->push_back(number);
            number = "";
        }

        int priority = getOperationPriority(ch);
        int lastPriority = 0;
        if (!operationStack.empty())
            lastPriority = getOperationPriority(operationStack.get().at(0));

        if (lastPriority < priority) {
            operationStack.push(std::string(1, ch));
        } else {
            while (lastPriority >= priority && !operationStack.empty()) {
                result->push_back(operationStack.get());
                operationStack.pop();
            }
            operationStack.push(std::string(1, ch));
        }
    }

    if (!number.empty())
        result->push_back(number);

    while (!operationStack.empty()) {
        result->push_back(operationStack.get());
        operationStack.pop();
    }
    return result;
}

int getOperationPriority(const char ch) {
    int priority;
    switch (ch) {
        case '-':
        case '+':
            priority = 1;
            break;
        case '/':
        case '*':
            priority = 2;
            break;
        default:
            std::cout << "String have unknown operation" << std::endl;
            exit(-1);
    }
    return priority;
}
