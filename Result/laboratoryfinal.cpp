#include <iostream>
#include <cctype>
#include <vector>
#include <stack>

void calculate(const std::string& input);
std::vector<std::string> *calculateOrder(const std::string& input);
int getOperationPriority(char ch);

int main() {
    std::string input;
    //std::cout << "Input calculation string:" << std::endl;
    //std::cin >> input;
    calculate("1+2*2/2");
    return 0;
}

void calculate(const std::string& input) {
    std::vector<std::string> *inputVector = calculateOrder(input);
    std::stack<double> numbers;

    std::cout << "Calculating order: ";
    for (auto str : *inputVector) {
        std::cout << str;
        if (str.find_first_not_of("0123456789") == std::string::npos) {
            numbers.push(std::stoi(str));
            continue;
        }
        const char ch = str.at(0);
        double first, second, result;
        second = numbers.top();
        numbers.pop();
        first = numbers.top();
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
    std::cout << std::endl;
    std::cout << "Calculation result: "<< numbers.top() << std::endl;
}

std::vector<std::string> *calculateOrder(const std::string& input) {
    std::vector<char> operationStack;

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
            lastPriority = getOperationPriority(operationStack.back());

        while (lastPriority >= priority && !operationStack.empty()) {
            result->push_back(std::string(1, operationStack.back()));
            operationStack.pop_back();
            priority = getOperationPriority(ch);
            lastPriority = getOperationPriority(operationStack.back());
        }
        operationStack.push_back(ch);

        for (const auto& c : *result) {
            std::cout << c;
        }
        std::cout << std::endl;

        for (auto c : operationStack) {
            std::cout << c;
        }
        std::cout << std::endl;
    }

    if (!number.empty())
        result->push_back(number);

    while (!operationStack.empty()) {
        result->push_back(std::string(1, operationStack.back()));
        operationStack.pop_back();
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
        case '(':
        case ')':
            priority = 3;
            break;
        default:
            std::cout << "String have unknown operation" << std::endl;
            exit(-1);
    }
    return priority;
}
