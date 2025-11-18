#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

int main(int argc, char** argv) {
    std::istream* in = &std::cin;
    std::ifstream file;

    // Если передан аргумент - читаем команды из файла
    if (argc > 1) {
        file.open(argv[1]);
        if (!file.is_open()) {
            std::cerr << "Cannot open file: " << argv[1] << "\n";
            return 1;
        }
        in = &file;
    }

    Stack st;
    int vars[4] = { 0,0,0,0 };
    std::string op;

    while (*in >> op) {
        if (op == "bipush") {
            int x; *in >> x;
            st.push(x);
        }
        else if (op == "pop") {
            if (st.empty()) { std::cerr << "Error: empty stack\n"; return 1; }
            st.pop();
        }
        else if (op == "iadd") {
            int a = st.get(); st.pop();
            int b = st.get(); st.pop();
            st.push(a + b);
        }
        else if (op == "isub") {
            int a = st.get(); st.pop();
            int b = st.get(); st.pop();
            st.push(b - a);
        }
        else if (op == "imul") {
            int a = st.get(); st.pop();
            int b = st.get(); st.pop();
            st.push(a * b);
        }
        else if (op == "iand") {
            int a = st.get(); st.pop();
            int b = st.get(); st.pop();
            st.push(a & b);
        }
        else if (op == "ior") {
            int a = st.get(); st.pop();
            int b = st.get(); st.pop();
            st.push(a | b);
        }
        else if (op == "ixor") {
            int a = st.get(); st.pop();
            int b = st.get(); st.pop();
            st.push(a ^ b);
        }
        else if (op == "iload_0") st.push(vars[0]);
        else if (op == "iload_1") st.push(vars[1]);
        else if (op == "iload_2") st.push(vars[2]);
        else if (op == "iload_3") st.push(vars[3]);
        else if (op == "istore_0") { vars[0] = st.get(); st.pop(); }
        else if (op == "istore_1") { vars[1] = st.get(); st.pop(); }
        else if (op == "istore_2") { vars[2] = st.get(); st.pop(); }
        else if (op == "istore_3") { vars[3] = st.get(); st.pop(); }
        else if (op == "swap") {
            int a = st.get(); st.pop();
            int b = st.get(); st.pop();
            st.push(a); st.push(b);
        }
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
    for (int i = 0; i < 4; i++)
        std::cout << vars[i] << "\n";

    return 0;
}
