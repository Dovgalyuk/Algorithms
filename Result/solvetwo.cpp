//
// Created by EMIL on 10.12.2021.
//

#include <iostream>

#include "stack.h"

static const std::string PUSH_COMMAND = "PUSH";
static const std::string POP_COMMAND = "POP";

bool isNumber(const std::string &str);

int main() {
    Stack<int> inputStack;

    Stack<int> A;
    Stack<int> B;
    Stack<int> C;
    Stack<int> D;

    std::string cmd;
    while(cmd != "EXIT") {
        std::cin >> cmd;
        if (cmd == "EXIT") break;

        std::string param;
        std::cin >> param;
        if (cmd == PUSH_COMMAND) {
            if (isNumber(param)) {
                inputStack.push(std::stoi(param));
            } else {
                switch(param[0]) {
                    case 'A':
                        inputStack.push(A.get());
                        break;
                    case 'B':
                        inputStack.push(B.get());
                        break;
                    case 'C':
                        inputStack.push(C.get());
                        break;
                    case 'D':
                        inputStack.push(D.get());
                        break;
                }
            }
        } else {
            const int data = inputStack.get();
            inputStack.pop();
            switch(param[0]) {
                case 'A':
                    A.push(data);
                    break;
                case 'B':
                    B.push(data);
                    break;
                case 'C':
                    C.push(data);
                    break;
                case 'D':
                    D.push(data);
                    break;
            }
        }
    }

    std::cout << "A = " << ((A.size() == 0) ? 0 : A.get()) << std::endl;
    std::cout << "B = " << ((B.size() == 0) ? 0 : B.get()) << std::endl;
    std::cout << "C = " << ((C.size() == 0) ? 0 : C.get()) << std::endl;
    std::cout << "D = " << ((D.size() == 0) ? 0 : D.get()) << std::endl;
    return 0;
}

bool isNumber(const std::string &str) {
    return str.find_first_not_of("0123456789") == std::string::npos;
}
