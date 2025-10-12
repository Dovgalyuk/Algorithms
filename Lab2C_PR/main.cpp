#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "stack.h"

using namespace std;

// Проверка.

static bool is_int_token(const string& t) {
    if (t.empty())
        return false;

    size_t i = 0;
    if (t[0] == '+' || t[0] == '-')
        i = 1;
    if (i == t.size())
        return false;

    for (; i < t.size(); ++i)
        if (!isdigit(static_cast<unsigned char>(t[i])))
            return false;

    return true;
}

// Снять два верхних элемента стека.

static bool pop2(Stack* s, Data& a, Data& b) {
    if (stack_empty(s))
        return false;

    a = stack_get(s); stack_pop(s);
    if (stack_empty(s)) {
        stack_push(s, a);
        return false;
    }

    b = stack_get(s); stack_pop(s);
    return true;
}

// Снять три верхних элемента стека.

static bool pop3(Stack* s, Data& a, Data& b, Data& c) {
    if (stack_empty(s))
        return false;

    a = stack_get(s); stack_pop(s);
    if (stack_empty(s)) {
        stack_push(s, a);
        return false;
    }

    b = stack_get(s); stack_pop(s);
    if (stack_empty(s)) {
        stack_push(s, b);
        stack_push(s, a);
        return false;
    }

    c = stack_get(s); stack_pop(s);
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 2)
        return 0;

    ifstream in(argv[1]);
    if (!in.is_open())
        return 0;

    Stack* st = stack_create();
    string tok;

    while (in >> tok) {
        for (char& ch : tok)
            ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));

        if (is_int_token(tok)) {
            int val = stoi(tok);
            stack_push(st, val);
        }
        else if (tok == "+") {
            Data a, b;
            if (pop2(st, a, b))
                stack_push(st, b + a);
        }
        else if (tok == "-") {
            Data a, b;
            if (pop2(st, a, b))
                stack_push(st, b - a);
        }
        else if (tok == "*") {
            Data a, b;
            if (pop2(st, a, b))
                stack_push(st, b * a);
        }
        else if (tok == "/") {
            Data a, b;
            if (pop2(st, a, b)) {
                if (a != 0)
                    stack_push(st, b / a);
                else {
                    stack_push(st, b);
                    stack_push(st, a);
                }
            }
        }
        else if (tok == "%") {
            Data a, b;
            if (pop2(st, a, b)) {
                if (a != 0)
                    stack_push(st, b % a);
                else {
                    stack_push(st, b);
                    stack_push(st, a);
                }
            }
        }
        else if (tok == "dup") {
            if (!stack_empty(st)) {
                Data a = stack_get(st);
                stack_push(st, a);
            }
        }
        else if (tok == "drop") {
            if (!stack_empty(st))
                stack_pop(st);
        }
        else if (tok == "swap") {
            Data a, b;
            if (pop2(st, a, b)) {
                stack_push(st, a);
                stack_push(st, b);
            }
        }
        else if (tok == "over") {
            if (!stack_empty(st)) {
                Data a = stack_get(st); stack_pop(st);
                if (stack_empty(st))
                    stack_push(st, a);
                else {
                    Data b = stack_get(st);
                    stack_push(st, a);
                    stack_push(st, b);
                }
            }
        }
        else if (tok == "rot") {
            Data a, b, c;
            if (pop3(st, a, b, c)) {
                stack_push(st, b);
                stack_push(st, a);
                stack_push(st, c);
            }
        }
        else if (tok == ".") {
            if (!stack_empty(st)) {
                cout << stack_get(st) << "\n";
                stack_pop(st);
            }
        }
    }

    stack_delete(st);
    return 0;
}