#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

using namespace std;

void printError() {
    cout << "Error" << endl;
    exit(1);
}

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    ifstream fin(argv[1]);
    if (!fin.is_open()) return 1;
    Stack stack;
    int regs[4] = {0, 0, 0, 0};
    string op;
    while (fin >> op) {
        if (op == "PUSH") {
            string arg;
            if (!(fin >> arg)) printError();
            if (arg.length() == 1 && arg[0] >= 'A' && arg[0] <= 'D') stack.push(regs[arg[0] - 'A']);
            else stack.push(stoi(arg));
        }
        else if (op == "POP") {
            string arg;
            if (!(fin >> arg)) printError();
            if (stack.empty() || arg.length() != 1 || arg[0] < 'A' || arg[0] > 'D') printError();
            regs[arg[0] - 'A'] = stack.get();
            stack.pop();
        }
        else if (op == "ADD" || op == "SUB" || op == "MUL") {
            string arg;
            if (!(fin >> arg)) printError();
            if (stack.empty()) printError();
            int op2 = stack.get();
            stack.pop();
            if (stack.empty()) printError();
            int op1 = stack.get();
            stack.pop();
            int res = 0;
            if (op == "ADD") res = op1 + op2;
            else if (op == "SUB") res = op1 - op2;
            else if (op == "MUL") res = op1 * op2;
            if (arg.length() != 1 || arg[0] < 'A' || arg[0] > 'D') printError();
            regs[arg[0] - 'A'] = res;
        }
        else printError();
    }
    cout << "A = " << regs[0] << "\n" << "B = " << regs[1] << "\n"
        << "C = " << regs[2] << "\n" << "D = " << regs[3] << "\n";
    return 0;
}
