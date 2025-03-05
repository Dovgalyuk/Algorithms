#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// Функция для определения приоритета операций
int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Функция для преобразования инфиксного выражения в постфиксное
string infixToPostfix(istream* input) {         //(1+2)*3 -> 12+3*
    string expression;
    getline(*input, expression); 

    stack<char> operators;
    string postfix;

    for (char ch : expression) {
        if (isdigit(ch)) {
            postfix += ch; // Добавляем цифру в постфиксное выражение
        }
        else if (ch == '(') {
            operators.push(ch);
        }
        else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop(); // Удаляем '(' из стека
        }
        else {
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(ch)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(ch);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

// Функция для генерации ассемблерных команд из постфиксного выражения
void generateAssembly(const string& postfix) {
    vector<string> assembly;

    for (char ch : postfix) {
        if (isdigit(ch)) {
            assembly.push_back("PUSH " + string(1, ch));
        }
        else {
            assembly.push_back("POP A");
            assembly.push_back("POP B");
            if (ch == '+') {
                assembly.push_back("ADD A, B");
            }
            else if (ch == '*') {
                assembly.push_back("MUL A, B");
            }
            else if (ch == '-') {
                assembly.push_back("SUB A, B");
            }
            assembly.push_back("PUSH A");
        }
    }

    for (const auto& line : assembly) {
        cout << line << endl;
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    istream* input = &cin;
    ifstream inputFile;

    if (argc >= 2) {
        inputFile.open(argv[1]);
        if (!inputFile) {
            cerr << "Ошибка: не удалось открыть файл " << argv[1] << endl;
            return 1;
        }
        input = &inputFile;
    }

    string postfix = infixToPostfix(input); // Преобразуем инфиксное выражение в постфиксное
    generateAssembly(postfix); // Генерируем ассемблерные команды

    return 0;
}