#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "../LibraryCPP/stack.h"

using namespace std;

struct Op {
    string name;
    int arg = 0;
    bool has_arg = false;
};

void error(Stack* st) {
    cout << "error\n";
    stack_delete(st);
    exit(0);
}

int main() {
    vector<Op> program;
    string line;

    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Op op;
        ss >> op.name;
        if (ss >> op.arg) op.has_arg = true;
        program.push_back(op);
    }

    int vars[4] = {0, 0, 0, 0};
    Stack* st = stack_create();

    int pc = 0;
    while (pc < (int)program.size()) {
        const auto& op = program[pc];

        if (op.name == "bipush") {
            if (!op.has_arg) error(st);
            stack_push(st, op.arg);
        }
        else if (op.name == "pop") {
            if (stack_empty(st)) error(st);
            stack_pop(st);
        }
        else if (op.name.rfind("iload_", 0) == 0) {
            int idx = op.name.back() - '0';
            stack_push(st, vars[idx]);
        }
        else if (op.name.rfind("istore_", 0) == 0) {
            if (stack_empty(st)) error(st);
            int idx = op.name.back() - '0';
            vars[idx] = stack_get(st);
            stack_pop(st);
        }
        else if (op.name == "swap") {
            if (stack_empty(st)) error(st);
            int a = stack_get(st); stack_pop(st);
            if (stack_empty(st)) error(st);
            int b = stack_get(st); stack_pop(st);
            stack_push(st, a);
            stack_push(st, b);
        }
        else if (op.name == "iadd" || op.name == "isub" ||
                 op.name == "imul" || op.name == "iand" ||
                 op.name == "ior"  || op.name == "ixor") {
            if (stack_empty(st)) error(st);
            int b = stack_get(st); stack_pop(st);
            if (stack_empty(st)) error(st);
            int a = stack_get(st); stack_pop(st);
            int r = 0;
            if (op.name == "iadd") r = a + b;
            else if (op.name == "isub") r = a - b;
            else if (op.name == "imul") r = a * b;
            else if (op.name == "iand") r = a & b;
            else if (op.name == "ior")  r = a | b;
            else if (op.name == "ixor") r = a ^ b;
            stack_push(st, r);
        }
        else {
            error(st);
        }

        pc++;
    }

    cout << "stack:\n";
    while (!stack_empty(st)) {
        cout << stack_get(st) << "\n";
        stack_pop(st);
    }

    cout << "vars:\n";
    for (int i = 0; i < 4; ++i)
        cout << vars[i] << "\n";

    stack_delete(st);
}
