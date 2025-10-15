#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>
#include "stack.h"

using namespace std;

int operpr(char poper) {
    switch (poper) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

int aoper(int pa, int pb, char poper) {
    switch (poper) {
    case '+':
        return pa + pb;
    case '-':
        return pa - pb;
    case '*':
        return pa * pb;
    case '/':
        if (pb == 0) throw std::runtime_error("Деление на 0");
        return pa / pb;
    default: throw std::runtime_error("Неподдерживаемый оператор");
    }
}

string foper(const string& pexp) {
    string res;
    Stack opers;

    for (size_t i = 0; i < pexp.length(); i++) {
        char c = pexp[i];
        if (c == ' ') continue;
        if (isdigit(c)) {
            while (i < pexp.length() && isdigit(pexp[i])) {
                res += pexp[i];
                i++;
            }
            i--;
            res += ' ';
        }
        else if (c == '(') {
            opers.push(c);
        }
        else if (c == ')') {
            while (!opers.empty() && opers.get() != '(') {
                res += (char)opers.get();
                res += ' ';
                opers.pop();
            }
            if (!opers.empty() && opers.get() == '(') {
                opers.pop();
            }
            else {
                throw runtime_error("Некорректное выражение");
            }
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!opers.empty() && opers.get() != '(' &&
                operpr((char)opers.get()) >= operpr(c)) {
                res += (char)opers.get();
                res += ' ';
                opers.pop();
            }
            opers.push(c);
        }
        else {
            throw runtime_error("Недопустимый символ");
        }
    }
    while (!opers.empty()) {
        if (opers.get() == '(') {
            throw runtime_error("Некорректное выражение");
        }
        res += (char)opers.get();
        res += ' ';
        opers.pop();
    }
    return res;
}

int fexpr(const string& rpn) {
    Stack values;
    string num;

    for (size_t i = 0; i < rpn.length(); i++) {
        char c = rpn[i];

        if (c == ' ') {
            if (!num.empty()) {
                values.push(stoi(num));
                num.clear();
            }
            continue;
        }

        if (isdigit(c)) {
            num += c;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (values.empty()) {
                throw runtime_error("Недостаточно операндов");
            }
            int val2 = values.get();
            values.pop();

            if (values.empty()) {
                throw runtime_error("Недостаточно операндов");
            }
            int val1 = values.get();
            values.pop();

            int res = aoper(val1, val2, c);
            values.push(res);
        }
    }
    if (!num.empty()) {
        values.push(stoi(num));
    }
    if (values.empty()) {
        throw runtime_error("Пустое выражение");
    }
    int res = values.get();
    values.pop();

    if (!values.empty()) {
        throw runtime_error("Некорректное выражение");
    }
    return res;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }

    string expr = argv[1];

    try {
        string rpn = foper(expr);
        int res = fexpr(rpn);
        cout << res << endl;
        return 0;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
}
