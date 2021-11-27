#include <iostream>
#include <cctype>
#include <vector>
#include <deque>
#include <stack>
#include <map>
#include <unordered_map>
#include <chrono>

typedef std::pair<std::string, float> StringPair;

float calculateSubExpression(float first, float second, char ch);

void generateVariants(const std::string &input, bool dynamic = false);

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

    auto result = StringPair("", 0);
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

        const auto str = '(' + left.first + operation + right.first + ')';

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

float calculateSubExpression(float first, float second, char ch) {
    switch (ch) {
        case '-':
            return first - second;
        case '+':
            return first + second;
        case '*':
            return first * second;
        default:
            std::cout << "String have unknown operation " << ch << std::endl;
            exit(-1);
    }
}