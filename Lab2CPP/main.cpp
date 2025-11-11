#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "stack.h"
using namespace std;

struct Op {
    string name;
    int arg = 0;
    bool has_arg = false;
};

void error(Stack* st, int vars[4], const string& msg = "", Stack* call_stack = nullptr) {
    if (!msg.empty()) {
        cout << "Error: " << msg << "\n";
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
    if (call_stack) stack_delete(call_stack);
    exit(1);
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
    Stack* call_stack = stack_create();

    int pc = 0;
    while (pc < (int)program.size()) {
        const auto& op = program[pc];

        if (op.name == "bipush") {
            if (!op.has_arg) error(st, vars, "bipush requires an argument", call_stack);
            stack_push(st, op.arg);
        }
        else if (op.name == "pop") {
            if (stack_empty(st)) error(st, vars, "pop requires at least one value on the stack", call_stack);
            stack_pop(st);
        }
        else if (op.name.rfind("iload_", 0) == 0) {
            int idx = op.name.back() - '0';
            if (idx < 0 || idx > 3) error(st, vars, "invalid variable index", call_stack);
            stack_push(st, vars[idx]);
        }
        else if (op.name.rfind("istore_", 0) == 0) {
            if (stack_empty(st)) error(st, vars, "istore requires a value on the stack", call_stack);
            int idx = op.name.back() - '0';
            if (idx < 0 || idx > 3) error(st, vars, "invalid variable index", call_stack);
            vars[idx] = stack_get(st);
            stack_pop(st);
        }
        else if (op.name == "swap") {
            if (stack_empty(st)) error(st, vars, "swap requires at least two values on the stack", call_stack);
            int a = stack_get(st); stack_pop(st);
            if (stack_empty(st)) error(st, vars, "swap requires at least two values on the stack", call_stack);
            int b = stack_get(st); stack_pop(st);
            stack_push(st, a);
            stack_push(st, b);
        }
        else if (op.name == "iadd" || op.name == "isub" ||
                 op.name == "imul" || op.name == "iand" ||
                 op.name == "ior" || op.name == "ixor") {
            if (stack_empty(st)) error(st, vars, "Arithmetic operation requires at least two values on the stack", call_stack);
            int b = stack_get(st); stack_pop(st);
            if (stack_empty(st)) error(st, vars, "Arithmetic operation requires at least two values on the stack", call_stack);
            int a = stack_get(st); stack_pop(st);
            int r = 0;
            if (op.name == "iadd") r = a + b;
            else if (op.name == "isub") r = a - b;
            else if (op.name == "imul") r = a * b;
            else if (op.name == "iand") r = a & b;
            else if (op.name == "ior") r = a | b;
            else if (op.name == "ixor") r = a ^ b;
            stack_push(st, r);
        }
        else if (op.name == "invokestatic") {
            if (!op.has_arg) error(st, vars, "invokestatic requires an argument", call_stack);
            if (op.arg < 0 || op.arg >= (int)program.size()) error(st, vars, "invalid call address", call_stack);
            stack_push(call_stack, pc + 1);
            pc = op.arg;
            continue;
        }
        else if (op.name == "return") {
            if (stack_empty(call_stack)) error(st, vars, "return requires an address in the call stack", call_stack);
            pc = stack_get(call_stack);
            stack_pop(call_stack);
            continue;
        }
        else if (op.name == "goto") {
            if (!op.has_arg) error(st, vars, "goto requires an argument", call_stack);
            if (op.arg < 0 || op.arg >= (int)program.size()) error(st, vars, "invalid jump address", call_stack);
            pc = op.arg;
            continue;
        }
        else {
            error(st, vars, "Unknown operation: " + op.name, call_stack);
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
    stack_delete(call_stack);
}
