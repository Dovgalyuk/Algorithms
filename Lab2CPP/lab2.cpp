#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

int main(int argc, char** argv) {
    std::istream* in = &std::cin;
    std::ifstream file;

    if (argc > 1) {
        file.open(argv[1]);
        if (!file.is_open()) {
            std::cerr << "Cannot open file: " << argv[1] << "\n";
            return 1;
        }
        in = &file;
    }

    Stack st;
    int vars[4] = { 0, 0, 0, 0 };
    std::string op;
    int callDepth = 0;
    int stackCount = 0;

    while (*in >> op) {
        if (op == "bipush") {
            int x; *in >> x;
            st.push(x);
            stackCount++;
        }
        else if (op == "pop") {
            if (st.empty()) { std::cerr << "Error: empty stack\n"; return 1; }
            st.pop();
            stackCount--;
        }
        else if (op == "swap") {
            if (stackCount < 2) { std::cerr << "Error: not enough elements to swap\n"; return 1; }
            int a = st.get(); st.pop();
            int b = st.get(); st.pop();
            st.push(a); st.push(b);
        }
        else if (op == "invokestatic") {
            int addr; *in >> addr;
            st.push(addr);
            callDepth++;
            stackCount++;
        }
        else if (op == "return") {
            if (callDepth == 0) {
                std::cerr << "Error: return without matching invokestatic\n";
                return 1;
            }
            if (stackCount != 1) {
                std::cerr << "Error: invalid stack state before return\n";
                return 1;
            }
            st.pop();
            callDepth--;
            stackCount--;
        }

        else if (op == "iadd" || op == "isub" || op == "imul" ||
            op == "iand" || op == "ior" || op == "ixor") {
            if (stackCount < 2) { std::cerr << "Error: not enough elements on stack\n"; return 1; }
            int a = st.get(); st.pop();
            int b = st.get(); st.pop();
            stackCount -= 2;

            if (op == "iadd") st.push(a + b);
            else if (op == "isub") st.push(b - a);
            else if (op == "imul") st.push(a * b);
            else if (op == "iand") st.push(a & b);
            else if (op == "ior") st.push(a | b);
            else if (op == "ixor") st.push(a ^ b);

            stackCount++;
        }

        else if (op == "iload_0") { st.push(vars[0]); stackCount++; }
        else if (op == "iload_1") { st.push(vars[1]); stackCount++; }
        else if (op == "iload_2") { st.push(vars[2]); stackCount++; }
        else if (op == "iload_3") { st.push(vars[3]); stackCount++; }

        else if (op == "istore_0") { if (st.empty()) { std::cerr << "Error: empty stack\n"; return 1; } vars[0] = st.get(); st.pop(); stackCount--; }
        else if (op == "istore_1") { if (st.empty()) { std::cerr << "Error: empty stack\n"; return 1; } vars[1] = st.get(); st.pop(); stackCount--; }
        else if (op == "istore_2") { if (st.empty()) { std::cerr << "Error: empty stack\n"; return 1; } vars[2] = st.get(); st.pop(); stackCount--; }
        else if (op == "istore_3") { if (st.empty()) { std::cerr << "Error: empty stack\n"; return 1; } vars[3] = st.get(); st.pop(); stackCount--; }

        else {
            std::cerr << "Unknown operation: " << op << "\n";
            return 1;
        }
    }
    std::cout << "stack:\n";
    while (!st.empty()) {
        std::cout << st.get() << "\n";
        st.pop();
    }

    std::cout << "vars:\n";
    for (int i = 0; i < 4; ++i) std::cout << vars[i] << "\n";

    return 0;
}
