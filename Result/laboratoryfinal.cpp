#include <iostream>
#include <cctype>
#include <vector>
#include <deque>
#include <stack>
#include <map>
#include <chrono>

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

typedef std::pair<std::string, float> StringPair;
typedef std::deque<StringPair> PairSVector; //first for print, second for calculating
typedef std::deque<std::string> SVector;
typedef std::deque<std::pair<int,char>> CVector;

float calculate(const std::string& input);
SVector *calculateOrder(const std::string& input);
int getOperationPriority(char ch, int code);
float calculateSubExpression(float first, float second, char ch, bool dynamic = false);

void generateVariants(const std::string &input, bool dynamic);
StringPair dynamicGenerateVariant(PairSVector numbers, CVector operations, const std::vector<int>& operationsPriority, bool dynamic);

bool mapContains(std::map<std::string, float>& map, const std::string& key);

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
    std::string input = "1+2-3*4-5*6+7*8-9*10";
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
    PairSVector numbers;
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
            numbers.push_back(StringPair(number, std::stof(number)));
            number = "";
        }
        operations.push_back(std::pair<int, char>(0, ch));
        operationsPriority.push_back(i);
        i++;
    }
    if (!number.empty()) numbers.push_back(StringPair(number, std::stof(number)));

    auto result = dynamicGenerateVariant(numbers, operations, operationsPriority, dynamic);
    while(std::next_permutation(operationsPriority.begin(), operationsPriority.end())) {
        auto candidateResult = dynamicGenerateVariant(numbers, operations, operationsPriority, dynamic);
        if (result.first <= candidateResult.first) continue;
        result = candidateResult;
    }
    std::cout << "String is: " << result.first << std::endl;
    std::cout << "Max number is: " << result.second << std::endl;
}

StringPair dynamicGenerateVariant(PairSVector numbers, CVector operations, const std::vector<int>& operationsPriority, bool dynamic) {
    int i = 0;
    for (int priority : operationsPriority) {

        // String building
        auto operation = operations.at(priority);
        std::string left = numbers.at(priority - operation.first).first;
        std::string right = numbers.at(priority + 1 - operation.first).first;;
        std::string str;
        if (i != operations.size() - 1)
            str = '(';
        str.append(left);
        str.append(std::string(1, operation.second));
        str.append(right);
        if (i != operations.size() - 1)
            str.append(")");
        numbers[priority - operation.first].first = str;
        //

        // Calculation
        if (dynamic) {
            float firstNum = numbers.at(priority - operation.first).second;
            float secondNum = numbers.at(priority + 1 - operation.first).second;
            const float calculationSubResult = calculateSubExpression(firstNum, secondNum, operation.second);
            numbers[priority - operation.first].second = calculationSubResult;
        }
        //

        numbers.erase(numbers.begin() + priority + 1 - operation.first);
        std::for_each(operations.begin() + priority, operations.end(), [](std::pair<int, char> &ch) {
            ch.first++;
        });
        i++;
    }

    if (!dynamic) numbers.front().second = calculate(numbers.front().first);
    return numbers.front();
}

float calculateSubExpression(float first, float second, char ch, bool dynamic) {
    static std::map<std::string, float> subExpressionMap;
    std::string key;
    key.append(std::to_string(first));
    key.append(std::to_string(ch));
    key.append(std::to_string(second));
    if (dynamic && mapContains(subExpressionMap, key)) return subExpressionMap.at(key);

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
    if (dynamic) subExpressionMap.insert(StringPair(key, result));
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

bool mapContains(std::map<std::string, float>& map, const std::string& key) {
    return map.find(key) != map.end();
}
