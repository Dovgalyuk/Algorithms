#include <iostream>
#include <cctype>
#include <vector>
#include <deque>
#include <stack>

/*
     Алгоритм перебора скобок для выражения
     Можно разделить операнды и операци
     получится два массива [1, 2, 3, 4] & [+, -, *]
     а изначальное выражение выделить в отдельный массив
     где каждое число или операция это отдельный элемент(к примеру в виде строки)
     после этого можно поменять местами операции (поменять приоритет)
     допустим получился такой вариант [2, 0, 1] значит будет такой порядок [*, +, -] (т.к. операции могут повторяться)
     по индексам мы находим смежные элементы и формируем из них выражение, удалем лишний элемент и вставлем выражение
     таким образом получаем финальное выражение
 */

typedef std::deque<std::string> SVector;
typedef std::deque<std::pair<int,char>> CVector;

float calculate(const std::string& input);
SVector *calculateOrder(const std::string& input);
int getOperationPriority(char ch, int code);

void generateVariants(const std::string &input);
std::string generateVariant(SVector numbers, CVector operations, std::vector<int> operationsPriority);

int main() {
    std::string input = "1+2-3*4";
    if (input.empty()) {
        std::cout << "Input calculation string:" << std::endl;
        std::cin >> input;
    }
    generateVariants(input);
    return 0;
}

void generateVariants(const std::string &input) {
    SVector numbers;
    CVector operations;
    std::vector<int> operationsPriority;
    std::string number;
    int i = 0;
    for (auto ch : input) {
        if (std::isdigit(ch)) {
            number += ch;
            continue;
        }
        if (!number.empty()) {
            numbers.push_back(number);
            number = "";
        }
        operations.push_back(std::pair<int, char>(0, ch));
        operationsPriority.push_back(i);
        i++;
    }
    if (!number.empty()) numbers.push_back(number);

    float max = calculate(generateVariant(numbers, operations, operationsPriority)); // For first variant
    while(std::next_permutation(operationsPriority.begin(), operationsPriority.end())) {
        float result = calculate(generateVariant(numbers, operations, operationsPriority));
        max = std::max(max, result);
    }
    std::cout << "Max number is: " << max << std::endl;
}

std::string generateVariant(SVector numbers, CVector operations, std::vector<int> operationsPriority) {
    int i = 0;
    for (int priority : operationsPriority) {
        auto operation = operations.at(priority);
        std::string left = numbers.at(priority - operation.first);
        std::string right = numbers.at(priority + 1 - operation.first);
        std::string finalString;
        if (i != operations.size() - 1)
            finalString = '(';
        finalString.append(left);
        finalString.append(std::string(1, operation.second));
        finalString.append(right);
        if (i != operations.size() - 1)
            finalString.append(")");
        numbers[priority - operation.first] = finalString;
        numbers.erase(numbers.begin() + priority + 1 - operation.first);
        std::for_each(operations.begin() + priority, operations.end(), [](std::pair<int, char> &ch) {
            ch.first++;
        });
        i++;
    }
    return numbers.front();
}

float calculate(const std::string& input) {
    SVector *inputVector = calculateOrder(input);
    std::stack<double> numbers;

    std::cout << "Calculating string: " << input << std::endl;
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
    return numbers.top();
}

SVector *calculateOrder(const std::string& input) {
    std::vector<char> operationStack;

    std::string number;
    auto *result = new SVector;

    for (char ch : input) {
        if (std::isdigit(ch)) {
            number.push_back(ch);
            continue;
        }
        if (!number.empty()) {
            result->push_back(number);
            number = "";
        }

        int priority = getOperationPriority(ch, 1);
        int lastPriority = 0;
        if (!operationStack.empty()) {
            lastPriority = getOperationPriority(operationStack.back(), 2);
            if (operationStack.back() == '(')
                lastPriority = 0;
        }

        if (ch == ')') {
            while (true) {
                if (operationStack.back() == '(') {
                    operationStack.pop_back();
                    break;
                }
                result->push_back(std::string(1, operationStack.back()));
                operationStack.pop_back();
            }
        } else {
            while (lastPriority >= priority && !operationStack.empty()) {

                result->push_back(std::string(1, operationStack.back()));
                operationStack.pop_back();

                if (operationStack.empty()) break;

                priority = getOperationPriority(ch, 3);
                lastPriority = getOperationPriority(operationStack.back(), 4);
            }
            operationStack.push_back(ch);
        }

        // Debug code
        /*for (const auto& c : *result) {
            std::cout << c;
        }
        std::cout << std::endl;

        for (auto c : operationStack) {
            std::cout << c;
        }
        std::cout << std::endl;*/
    }

    if (!number.empty())
        result->push_back(number);

    while (!operationStack.empty()) {
        result->push_back(std::string(1, operationStack.back()));
        operationStack.pop_back();
    }
    return result;
}

int getOperationPriority(const char ch, int code) {
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
        case ')':
        case '(':
            priority = 3;
            break;
        default:
            std::cout << "String have unknown operation [PRIORITY] " << ch << " " << code << std::endl;
            exit(-1);
    }
    return priority;
}
