#include <iostream>
#include <cctype>
#include <vector>
#include <deque>
#include <stack>
#include <map>
#include <chrono>

typedef std::pair<std::string, float> StringPair;
typedef std::pair<bool, std::string> KeyPair;

float calculateSubExpression(float first, float second, char ch);

void generateVariants(const std::string &input, bool dynamic = false);

struct Finder {
    std::string inputString;
    std::vector<float> numbers;
    std::string operations;
    std::map<KeyPair, StringPair> subExpressionMap;

    StringPair findMax(int leftIndex, int rightIndex, bool dynamic, bool findMin = false) {
        KeyPair key;
        if (dynamic) {
            key.first = findMin;
            key.second = inputString.substr(leftIndex * 2, (rightIndex + 1) * 2 + 1 - leftIndex * 2);
            const auto pair = subExpressionMap.find(key);
            if (pair != subExpressionMap.end()) {
                return pair->second;
            }
        }
        StringPair result = StringPair("", 0);
        for (int i = leftIndex; i <= rightIndex; i++) {
            const char operation = operations.at(i);

            StringPair left;
            StringPair right;

            if (i == leftIndex) {
                left = StringPair(std::to_string((int) numbers.at(leftIndex)), numbers.at(leftIndex));
            } else {
                left = findMax(leftIndex, i - 1, dynamic);
            }

            if (i == rightIndex) {
                right = StringPair(std::to_string((int) numbers.at(rightIndex + 1)), numbers.at(rightIndex + 1));
            } else {
                right = findMax(i + 1, rightIndex, dynamic, (operation == '-'));
            }

            const auto str = '(' + left.first + operation + right.first + ')';
            const float tmpNum = calculateSubExpression(left.second, right.second, operation);
            const StringPair tmpSP = StringPair(str, tmpNum);

            if (result.first.empty()) {
                result = tmpSP;
                continue;
            }
            if (findMin) {
                if (result.second > tmpSP.second) result = tmpSP;
            } else {
                if (result.second < tmpSP.second) result = tmpSP;
            }
        }

        if (dynamic) subExpressionMap[key] = result;
        return result;
    }
};

int main() {
    std::vector<std::string> input = {
            "1+2",
            "1+2-3",
            "1+2-3*4",
            "1+2-3*4-5",
            "1+2-3*4-5*6",
            "1+2-3*4-5*6+7",
            "1+2-3*4-5*6+7*8",
            "1+2-3*4-5*6+7*8-9",
            "1+2-3*4-5*6+7*8-9*10",
            "1+2-3*4-5*6+7*8-9*10-11",
            "1+2-3*4-5*6+7*8-9*10-11*12",
            "1+2-3*4-5*6+7*8-9*10-11*12+13",
            "1+2-3*4-5*6+7*8-9*10-11*12+13*14",
            "1+2-3*4-5*6+7*8-9*10-11*12+13*14-15"
    };

    for (const auto &str : input) {
        //Non dynamic
        auto startTime = std::chrono::system_clock::now();
        generateVariants(str, false);
        auto endTime = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> finalTime = endTime - startTime;
        std::cout << "Find maximum without dynamic on " << str.size() << " chars take " << finalTime.count()
                  << " microseconds." << std::endl;

        //Dynamic
        startTime = std::chrono::system_clock::now();
        generateVariants(str, true);
        endTime = std::chrono::system_clock::now();
        finalTime = endTime - startTime;
        std::cout << "Find maximum with dynamic on " << str.size() << " chars take " << finalTime.count()
                  << " microseconds." << std::endl;
    }
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

    Finder finder;
    finder.numbers = numbers;
    finder.operations = operations;
    finder.inputString = input;
    const auto result = finder.findMax(0, operations.size() - 1, dynamic);
    //std::cout << "String is: " << result.first << std::endl;
    //std::cout << "Max number is: " << result.second << std::endl;
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