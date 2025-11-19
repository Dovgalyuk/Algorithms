#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "stack.h"

using namespace std;

struct Op {
    string name;
    int arg = 0;
    bool has_arg = false;
};

void error(Stack* st, Stack* flag_st, int vars[4], const string& msg = "") {
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
    stack_delete(flag_st);
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
    Stack* flag_st = stack_create();
    int depth = 0;

    int pc = 0;
    while (pc < (int)program.size()) {
        const Op& op = program[pc];

        if (op.name == "bipush") {
            if (!op.has_arg) error(st, flag_st, vars, "bipush requires an argument");
            stack_push(st, op.arg);
            stack_push(flag_st, 0);
            ++depth;
        }
        else if (op.name == "pop") {
            if (depth == 0) error(st, flag_st, vars, "pop requires at least one value on the stack");
            if (stack_get(flag_st) != 0) error(st, flag_st, vars, "pop with return address");
            stack_pop(st);
            stack_pop(flag_st);
            --depth;
        }
        else if (op.name.rfind("iload_", 0) == 0) {
            int idx = op.name.back() - '0';
            if (idx < 0 || idx > 3) error(st, flag_st, vars, "invalid variable index");
            stack_push(st, vars[idx]);
            stack_push(flag_st, 0);
            ++depth;
        }
        else if (op.name.rfind("istore_", 0) == 0) {
            if (depth == 0) error(st, flag_st, vars, "istore requires a value on the stack");
            int idx = op.name.back() - '0';
            if (idx < 0 || idx > 3) error(st, flag_st, vars, "invalid variable index");
            if (stack_get(flag_st) != 0) error(st, flag_st, vars, "store of return address");
            vars[idx] = stack_get(st);
            stack_pop(st);
            stack_pop(flag_st);
            --depth;
        }
        else if (op.name == "swap") {
            if (depth < 2) error(st, flag_st, vars, "swap requires at least two values on the stack");
            int a = stack_get(st); stack_pop(st);
            int af = stack_get(flag_st); stack_pop(flag_st);
            int b = stack_get(st); stack_pop(st);
            int bf = stack_get(flag_st); stack_pop(flag_st);
            depth -= 2;
            stack_push(st, a); stack_push(flag_st, af);
            stack_push(st, b); stack_push(flag_st, bf);
            depth += 2;
        }
        else if (op.name == "iadd" || op.name == "isub" || op.name == "imul" ||
                 op.name == "iand" || op.name == "ior" || op.name == "ixor") {
            if (depth < 2) error(st, flag_st, vars, "Arithmetic operation requires at least two values on the stack");

            int top_flag = stack_get(flag_st);
            stack_pop(flag_st);
            int second_flag = stack_get(flag_st);
            stack_push(flag_st, top_flag);

            if (top_flag != 0 || second_flag != 0)
                error(st, flag_st, vars, "Arithmetic operation with return address");

            int b = stack_get(st); stack_pop(st);
            stack_pop(flag_st);
            int a = stack_get(st); stack_pop(st);
            stack_pop(flag_st);
            depth -= 2;

            int r = 0;
            if (op.name == "iadd") r = a + b;
            else if (op.name == "isub") r = a - b;
            else if (op.name == "imul") r = a * b;
            else if (op.name == "iand") r = a & b;
            else if (op.name == "ior") r = a | b;
            else if (op.name == "ixor") r = a ^ b;

            stack_push(st, r);
            stack_push(flag_st, 0);
            ++depth;
        }
        else if (op.name == "invokestatic") {
            if (!op.has_arg) error(st, flag_st, vars, "invokestatic requires an argument");
            if (op.arg < 0 || op.arg >= (int)program.size()) error(st, flag_st, vars, "invalid call address");
            stack_push(st, pc + 1);
            stack_push(flag_st, 1);
            ++depth;
            pc = op.arg;
            continue;
        }
        else if (op.name == "return") {
            if (depth == 0) error(st, flag_st, vars, "return requires an address on the stack");
            if (stack_get(flag_st) == 0) error(st, flag_st, vars, "return with ordinary value");
            int addr = stack_get(st);
            stack_pop(st);
            stack_pop(flag_st);
            --depth;
            if (addr < 0 || addr >= (int)program.size()) error(st, flag_st, vars, "invalid return address");
            pc = addr;
            continue;
        }
        else if (op.name == "goto") {
            if (!op.has_arg) error(st, flag_st, vars, "goto requires an argument");
            if (op.arg < 0 || op.arg >= (int)program.size()) error(st, flag_st, vars, "invalid jump address");
            pc = op.arg;
            continue;
        }
        else {
            error(st, flag_st, vars, "Unknown operation: " + op.name);
        }

        ++pc;
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
    stack_delete(flag_st);
}
