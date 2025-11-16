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
    vector<bool> is_ret;

    int pc = 0;
    while (pc < (int)program.size()) {
        const Op& op = program[pc];

        if (op.name == "bipush") {
            if (!op.has_arg) error(st, vars, "bipush requires an argument");
            stack_push(st, op.arg);
            is_ret.push_back(false);
        }
        else if (op.name == "pop") {
            if (stack_empty(st)) error(st, vars, "pop requires at least one value on the stack");
            if (is_ret.back()) error(st, vars, "pop with return address");
            stack_pop(st);
            is_ret.pop_back();
        }
        else if (op.name.rfind("iload_", 0) == 0) {
            int idx = op.name.back() - '0';
            if (idx < 0 || idx > 3) error(st, vars, "invalid variable index");
            stack_push(st, vars[idx]);
            is_ret.push_back(false);
        }
        else if (op.name.rfind("istore_", 0) == 0) {
            if (stack_empty(st)) error(st, vars, "istore requires a value on the stack");
            int idx = op.name.back() - '0';
            if (idx < 0 || idx > 3) error(st, vars, "invalid variable index");
            if (is_ret.back()) error(st, vars, "store of return address");
            vars[idx] = stack_get(st);
            stack_pop(st);
            is_ret.pop_back();
        }
        else if (op.name == "swap") {
            if (is_ret.size() < 2) error(st, vars, "swap requires at least two values on the stack");
            int a = stack_get(st); stack_pop(st);
            bool a_ret = is_ret.back(); is_ret.pop_back();
            int b = stack_get(st); stack_pop(st);
            bool b_ret = is_ret.back(); is_ret.pop_back();
            stack_push(st, a); is_ret.push_back(a_ret);
            stack_push(st, b); is_ret.push_back(b_ret);
        }
        else if (op.name == "iadd" || op.name == "isub" || op.name == "imul" ||
                 op.name == "iand" || op.name == "ior" || op.name == "ixor") {
            if (is_ret.size() < 2) error(st, vars, "Arithmetic operation requires at least two values on the stack");
            if (is_ret.back() || is_ret[is_ret.size() - 2]) error(st, vars, "Arithmetic operation with return address");
            int b = stack_get(st); stack_pop(st);
            is_ret.pop_back();
            int a = stack_get(st); stack_pop(st);
            is_ret.pop_back();
            int r = 0;
            if (op.name == "iadd") r = a + b;
            else if (op.name == "isub") r = a - b;
            else if (op.name == "imul") r = a * b;
            else if (op.name == "iand") r = a & b;
            else if (op.name == "ior") r = a | b;
            else if (op.name == "ixor") r = a ^ b;
            stack_push(st, r);
            is_ret.push_back(false);
        }
        else if (op.name == "invokestatic") {
            if (!op.has_arg) error(st, vars, "invokestatic requires an argument");
            if (op.arg < 0 || op.arg >= (int)program.size()) error(st, vars, "invalid call address");
            stack_push(st, pc + 1);
            is_ret.push_back(true);
            pc = op.arg;
            continue;
        }
        else if (op.name == "return") {
            if (stack_empty(st)) error(st, vars, "return requires an address on the stack");
            if (!is_ret.back()) error(st, vars, "return with ordinary value");
            int addr = stack_get(st);
            stack_pop(st);
            is_ret.pop_back();
            if (addr < 0 || addr >= (int)program.size()) error(st, vars, "invalid return address");
            pc = addr;
            continue;
        }
        else if (op.name == "goto") {
            if (!op.has_arg) error(st, vars, "goto requires an argument");
            if (op.arg < 0 || op.arg >= (int)program.size()) error(st, vars, "invalid jump address");
            pc = op.arg;
            continue;
        }
        else {
            error(st, vars, "Unknown operation: " + op.name);
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
}
