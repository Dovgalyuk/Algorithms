#include <iostream>
#include <cctype>
#include <vector>
#include <deque>
#include <stack>
#include <map>
#include <unordered_map>
#include <chrono>

typedef std::pair<std::string, float> StringPair;
typedef std::deque<std::string> SVector;

float calculate(const std::string& input);
SVector *calculateOrder(const std::string& input);
int getOperationPriority(char ch, int code);
float calculateSubExpression(float first, float second, char ch, bool dynamic = false);

void generateVariants(const std::string &input, bool dynamic = false);

bool mapContains(std::unordered_map<std::string, float>& map, const std::string& key);

StringPair findMax(const std::vector<float> &numbers, const std::string &operations, bool dynamic, bool findMin = false);

int main() {
    /*
    "1+2"
    "1+2-3"
    "1+2-3*4"
    "1+2-3*4-5"
    "1+2-3*4-5*6"
    "1+2-3*4-5*6+7"
    "1+2-3*4-5*6+7*8"
    "1+2-3*4-5*6+7*8-9"
    "1+2-3*4-5*6+7*8-9*10"
     */
    std::string input = "1+2-3*4-5*6+7*8-9*10-11+12*13-14";
    if (input.empty()) {
        std::cout << "Input calculation string:" << std::endl;
        std::cin >> input;
    }

    //Non dynamic
    auto startTime = std::chrono::system_clock::now();
    generateVariants(input, false);
    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> finalTime = endTime - startTime;
    std::cout << "Find maximum without dynamic on " << input.size() << " chars take " << finalTime.count() << " milliseconds." << std::endl;

    //Dynamic
    startTime = std::chrono::system_clock::now();
    generateVariants(input, true);
    endTime = std::chrono::system_clock::now();
    finalTime = endTime - startTime;
    std::cout << "Find maximum with dynamic on " << input.size() << " chars take " << finalTime.count() << " milliseconds." << std::endl;

    return 0;
}

void generateVariants(const std::string &input, bool dynamic) {
    std::vector<float> numbers;
    std::string operations;
    std::vector<int> operationsPriority;
    std::string number;
    int i = 0;
    for (auto ch : input) {
        if (std::isdigit(ch)) {
            number += ch;
            continue;
        }
        if (!number.empty()) {
            numbers.push_back(std::stof(number));
            number = "";
        }
        operations.push_back(ch);
        operationsPriority.push_back(i);
        i++;
    }
    if (!number.empty()) numbers.push_back(std::stof(number));

    const auto result = findMax(numbers, operations, dynamic);
    std::cout << "String is: " << result.first << std::endl;
    std::cout << "Max number is: " << result.second << std::endl;
}

StringPair findMax(const std::vector<float> &numbers, const std::string &operations, bool dynamic, bool findMin) {
    static std::unordered_map<std::string, float> subExpressionMap;


    StringPair result = StringPair("", 0);
    for (int i = 0; i < operations.size(); i++) {
        const char operation = operations.at(i);

        StringPair left;
        StringPair right;

        std::vector<float> leftNum;
        std::string leftOper;

        if (i == 0) {
            left = StringPair(std::to_string((int) numbers.at(0)), numbers.at(0));
        } else {
            for (int j = 0; j <= i; j++) {
                leftNum.push_back(numbers.at(j));
                if (j >= i) continue;
                leftOper.push_back(operations.at(j));
            }
            left = findMax(leftNum, leftOper, dynamic);
        }

        std::vector<float> rightNum;
        std::string rightOper;

        if (i + 1 == operations.size()) {
            right = StringPair(std::to_string((int) numbers.at(numbers.size() - 1)), numbers.at(numbers.size() - 1));
        } else {
            for (int j = i + 1; j < numbers.size(); j++) {
                rightNum.push_back(numbers.at(j));
                if (j >= operations.size()) continue;
                rightOper.push_back(operations.at(j));
            }
            bool needMin = operation == '-';
            right = findMax(rightNum, rightOper, dynamic, needMin);
        }

        const std::string str = '(' + left.first + operation + right.first + ')';

        float tmpNum = 0;
        StringPair tmpSP;
        if (dynamic) {
            auto pair = subExpressionMap.find(str);
            if (pair != subExpressionMap.end()) {
                tmpNum = pair->second;
                tmpSP = StringPair(str, tmpNum);
            } else {
                tmpNum = calculateSubExpression(left.second, right.second, operation);
                tmpSP = StringPair(str, tmpNum);
                subExpressionMap[str] = tmpNum;
            }
        } else {
            tmpNum = calculateSubExpression(left.second, right.second, operation);
            tmpSP = StringPair(str, tmpNum);
        }

        if (result.first.empty()) {
            result = tmpSP;
            continue;
        }
        if (findMin) {
            if (result.second > tmpSP.second) result = tmpSP;
            continue;
        }
        if (result.second < tmpSP.second) result = tmpSP;
    }

    return result;
}

float calculateSubExpression(float first, float second, char ch, bool dynamic) {
    float result;
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
            std::cout << "String have unknown operation " << ch << std::endl;
            exit(-1);
    }
    return result;
}

float calculate(const std::string& input) {
    SVector *inputVector = calculateOrder(input);
    std::stack<float> numbers;

    //std::cout << "Calculating string: " << input << std::endl;
    //std::cout << "Calculating order: ";
    for (auto str : *inputVector) {
        //std::cout << str;
        if (str.find_first_not_of("0123456789") == std::string::npos) {
            numbers.push(std::stof(str));
            continue;
        }
        const char ch = str.at(0);
        float first, second, result;
        second = numbers.top();
        numbers.pop();
        first = numbers.top();
        numbers.pop();
        result = calculateSubExpression(first, second, ch);
        numbers.push(result);
    }
    //std::cout << std::endl;
    //std::cout << "Calculation result: "<< numbers.top() << std::endl;
    return numbers.top();
}

SVector *calculateOrder(const std::string& input) {
    std::vector<char> operationStack;

    std::string number;
    auto *result = new SVector;

    for (char ch : input) {
        if (std::isdigit(ch) || ch == '.') {
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
            std::cout << "String have unknown operation " << ch << " " << code << std::endl;
            exit(-1);
    }
    return priority;
}

bool mapContains(std::unordered_map<std::string, float>& map, const std::string& key) {
    return map.find(key) != map.end();
}
