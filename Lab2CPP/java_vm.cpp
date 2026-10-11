#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "stack.h"

using namespace std;

bool is_return_addr(int val) {
    return val < 0;
}

void error(const string& msg) {
    cerr << "Error: " << msg << endl;
    exit(1);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin.is_open()) {
        cerr << "Cannot open file: " << argv[1] << endl;
        return 1;
    }

    vector<string> lines;
    string line;
    while (getline(fin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        lines.push_back(line);
    }
    fin.close();

    Stack* stack = stack_create();
    int vars[4] = {0, 0, 0, 0};
    int pc = 0;
    int n = lines.size();

    while (pc < n) {
        string cmd = lines[pc];
        if (cmd.empty()) {
            pc++;
            continue;
        }

        istringstream iss(cmd);
        string op;
        iss >> op;

        if (op == "bipush") {
            int val;
            iss >> val;
            stack_push(stack, val);
        }
        else if (op == "pop") {
            if (stack_empty(stack)) error("stack underflow on pop");
            int val = stack_get(stack);
            if (is_return_addr(val)) error("pop return address");
            stack_pop(stack);
        }
        else if (op == "imul" || op == "iand" || op == "ior" || op == "ixor" || op == "iadd" || op == "isub") {
            if (stack_empty(stack)) error("stack underflow on " + op);
            int b = stack_get(stack);
            if (is_return_addr(b)) error("arithmetic with return address");
            stack_pop(stack);

            if (stack_empty(stack)) error("stack underflow on " + op);
            int a = stack_get(stack);
            if (is_return_addr(a)) error("arithmetic with return address");
            stack_pop(stack);

            int res = 0;
            if (op == "imul") res = a * b;
            else if (op == "iand") res = a & b;
            else if (op == "ior") res = a | b;
            else if (op == "ixor") res = a ^ b;
            else if (op == "iadd") res = a + b;
            else if (op == "isub") res = a - b;
            stack_push(stack, res);
        }
        else if (op == "iload_0" || op == "iload_1" || op == "iload_2" || op == "iload_3") {
            int idx = op[op.length() - 1] - '0';
            stack_push(stack, vars[idx]);
        }
        else if (op == "istore_0" || op == "istore_1" || op == "istore_2" || op == "istore_3") {
            int idx = op[op.length() - 1] - '0';
            if (stack_empty(stack)) error("stack underflow on " + op);
            int val = stack_get(stack);
            if (is_return_addr(val)) error("store return address");
            stack_pop(stack);
            vars[idx] = val;
        }
        else if (op == "swap") {
            if (stack_empty(stack)) error("stack underflow on swap");
            int a = stack_get(stack);
            if (is_return_addr(a)) error("swap return address");
            stack_pop(stack);
            if (stack_empty(stack)) error("stack underflow on swap");
            int b = stack_get(stack);
            if (is_return_addr(b)) error("swap return address");
            stack_pop(stack);
            stack_push(stack, a);
            stack_push(stack, b);
        }
        else if (op == "invokestatic") {
            int addr;
            iss >> addr;
            int ret_addr = pc + 1; // 0-based index of next line
            stack_push(stack, -ret_addr);
            cout << "call " << addr << endl;
            pc = addr - 1; // 1-based to 0-based
            continue;
        }
        else if (op == "return") {
            if (stack_empty(stack)) error("stack underflow on return");
            int val = stack_get(stack);
            if (!is_return_addr(val)) error("return with ordinary number");
            stack_pop(stack);
            pc = -val;
            continue;
        }
        else {
            error("unknown command: " + op);
        }

        pc++;
    }

    // Print stack
    cout << "stack:" << endl;
    Stack* temp = stack_create();
    while (!stack_empty(stack)) {
        int val = stack_get(stack);
        stack_push(temp, val);
        stack_pop(stack);
    }
    while (!stack_empty(temp)) {
        int val = stack_get(temp);
        cout << val << endl;
        stack_push(stack, val);
        stack_pop(temp);
    }
    stack_delete(temp);

    // Print vars
    cout << "vars:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << vars[i] << endl;
    }

    stack_delete(stack);
    return 0;
}