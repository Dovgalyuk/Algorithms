#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "stack.h"

using namespace std;

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*') return 2;
    return 0;
}

void print_op(char op, ostream &out) {
    out << "POP A\n";
    out << "POP B\n";
    if (op == '+') {
        out << "ADD A, B\n";
        out << "PUSH A\n";
    } else if (op == '*') {
        out << "MUL A, B\n";
        out << "PUSH A\n";
    } else if (op == '-') {
        out << "SUB B, A\n";
        out << "PUSH B\n";
    }
}

void parse(const string &s, ostream &out) {
    Stack *st = stack_create();
    size_t i = 0;

    while (i < s.length()) {
        char c = s[i];

        if (isspace(c)) {
            ++i;
            continue;
        }

        if (isalnum(c)) {
            string val = "";
            while (i < s.length() && isalnum(s[i])) {
                val += s[i];
                ++i;
            }
            out << "PUSH " << val << "\n";
        } else if (c == '(') {
            stack_push(st, '(');
            ++i;
        } else if (c == ')') {
            while (!stack_empty(st) && stack_get(st) != '(') {
                char op = (char)stack_get(st);
                stack_pop(st);
                print_op(op, out);
            }
            if (!stack_empty(st)) {
                stack_pop(st);
            }
            ++i;
        } else if (c == '+' || c == '-' || c == '*') {
            while (!stack_empty(st) && priority((char)stack_get(st)) >= priority(c)) {
                char op = (char)stack_get(st);
                stack_pop(st);
                print_op(op, out);
            }
            stack_push(st, c);
            ++i;
        } else {
            ++i;
        }
    }

    while (!stack_empty(st)) {
        char op = (char)stack_get(st);
        stack_pop(st);
        print_op(op, out);
    }

    stack_delete(st);
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        cerr << "Usage: " << argv[0] << " <input_file> [output_file]\n";
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin.is_open()) {
        cerr << "Cannot open input file\n";
        return 1;
    }

    ofstream fout;
    ostream *out = &cout;
    if (argc == 3) {
        fout.open(argv[2]);
        if (!fout.is_open()) {
            cerr << "Cannot open output file\n";
            return 1;
        }
        out = &fout;
    }

    string line;
    while (getline(fin, line)) {
        if (!line.empty()) {
            parse(line, *out);
        }
    }

    return 0;
}
