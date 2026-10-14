#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "stack.h"

using namespace std;

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

    Stack* data_stack = stack_create();
    Stack* return_stack = stack_create();
    
    int vars[4] = {0, 0, 0, 0};
    int pc = 0;
    int n = lines.size();
    
    int max_iterations = 100000;
    int iterations = 0;

    while (pc < n) {
        iterations++;
        if (iterations > max_iterations) {
            error("Infinite loop detected");
        }

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
            stack_push(data_stack, val);
        }
        else if (op == "pop") {
            if (stack_empty(data_stack)) error("stack underflow on pop");
            stack_pop(data_stack);
        }
        else if (op == "imul" || op == "iand" || op == "ior" || op == "ixor" || op == "iadd" || op == "isub") {
            if (stack_empty(data_stack)) error("stack underflow on " + op);
            int b = stack_get(data_stack);
            stack_pop(data_stack);

            if (stack_empty(data_stack)) error("stack underflow on " + op);
            int a = stack_get(data_stack);
            stack_pop(data_stack);

            int r = 0;
            if (op == "imul") r = a * b;
            else if (op == "iand") r = a & b;
            else if (op == "ior")  r = a | b;
            else if (op == "ixor") r = a ^ b;
            else if (op == "iadd") r = a + b;
            else if (op == "isub") r = a - b;
            stack_push(data_stack, r);
        }
        else if (op == "iload_0" || op == "iload_1" || op == "iload_2" || op == "iload_3") {
            int idx = op[op.length() - 1] - '0';
            stack_push(data_stack, vars[idx]);
        }
        else if (op == "istore_0" || op == "istore_1" || op == "istore_2" || op == "istore_3") {
            int i = op[op.size() - 1] - '0';
            if (stack_empty(data_stack)) error("stack underflow on " + op);
            int v = stack_get(data_stack);
            stack_pop(data_stack);
            vars[i] = v;
        }
        else if (op == "swap") {
            if (stack_empty(data_stack)) error("stack underflow on swap");
            int a = stack_get(data_stack);
            stack_pop(data_stack);
            if (stack_empty(data_stack)) error("stack underflow on swap");
            int b = stack_get(data_stack);
            stack_pop(data_stack);
            stack_push(data_stack, a);
            stack_push(data_stack, b);
        }
        else if (op == "invokestatic") {
            int addr;
            iss >> addr;
            int ret_addr = pc + 1; 
            stack_push(return_stack, ret_addr); 
            cout << "call " << addr << endl;
            pc = addr - 1; 
            continue;
        }
        else if (op == "return") {
            if (stack_empty(return_stack)) {
                break; 
            }
            int ret_addr = stack_get(return_stack);
            stack_pop(return_stack);
            pc = ret_addr; 
            continue;
        }
        else {
            error("unknown command: " + op);
        }

        pc++;
    }


    cout << "stack:" << endl;
    Stack* temp = stack_create();
    while (!stack_empty(data_stack)) {
        int val = stack_get(data_stack);
        stack_push(temp, val);
        stack_pop(data_stack);
    }
    while (!stack_empty(temp)) {
        int val = stack_get(temp);
        cout << val << endl;
        stack_push(data_stack, val);
        stack_pop(temp);
    }
    stack_delete(temp);


    cout << "vars:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << vars[i] << endl;
    }

    stack_delete(data_stack);
    stack_delete(return_stack);
    return 0;
}