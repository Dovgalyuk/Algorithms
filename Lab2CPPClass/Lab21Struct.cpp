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

void foper(Stack& pvalues, char proper) {
    if (pvalues.empty()) {
        throw runtime_error("Ошибка в выражении");
    }
    int val2 = pvalues.get();
    pvalues.pop();
    int val1 = pvalues.get();
    pvalues.pop();
    int res = aoper(val1, val2, proper);
    pvalues.push(res);
}

int fexpr(const string& pexp) {
    Stack vals;
    Stack opers;
    char op;
    for (size_t i = 0; i < pexp.length(); i++) {
        if (pexp[i] == ' ') {
            continue;
        }
        if (isdigit(pexp[i])) {
            int num = 0;
            string snum;
            while (i < pexp.length() && isdigit(pexp[i])) {
                snum += pexp[i];
                i++;
            }
            i--;
            num = stoi(snum);
            vals.push(num);
        }
        else if (pexp[i] == '(') {
            opers.push('(');
        }
        else if (pexp[i] == ')') {
            while (!opers.empty() && opers.get() != '(') {
                op = (char)opers.get();
                opers.pop();
                foper(vals, op);
            }
            if (!opers.empty()) {
                opers.pop();
            }
        }
        else if (pexp[i] == '+' || pexp[i] == '-' ||
            pexp[i] == '*' || pexp[i] == '/') {
            while (!opers.empty() && operpr((char)opers.get()) >= operpr(pexp[i])) {
                op = (char)opers.get();
                opers.pop();
                foper(vals, op);
            }
            opers.push(pexp[i]);
        }
        else {
            throw runtime_error("Ошибка в выражении");
        }
    }
    while (!opers.empty()) {
        op = (char)opers.get();
        opers.pop();
        foper(vals, op);
    }
    if (vals.empty()) {
        throw runtime_error("Ошибка в выражении");
    }
    return vals.get();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }
    string expr = argv[1];
    try {
        int res = fexpr(expr);
        cout << res << endl;
        return 0;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
}
