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

    int A;
    int B;
    int C;
    int D;

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
                        inputStack.push(A);
                        break;
                    case 'B':
                        inputStack.push(B);
                        break;
                    case 'C':
                        inputStack.push(C);
                        break;
                    case 'D':
                        inputStack.push(D);
                        break;
                }
            }
        } else {
            const int data = inputStack.get();
            inputStack.pop();
            switch(param[0]) {
                case 'A':
                    A = data;
                    break;
                case 'B':
                    B= data;
                    break;
                case 'C':
                    C= data;
                    break;
                case 'D':
                    D= data;
                    break;
            }
        }
    }

    std::cout << "A = " << ((A == 0) ? 0 : A) << std::endl;
    std::cout << "B = " << ((B == 0) ? 0 : B) << std::endl;
    std::cout << "C = " << ((C == 0) ? 0 : C) << std::endl;
    std::cout << "D = " << ((D == 0) ? 0 : D) << std::endl;
    return 0;
}

bool isNumber(const std::string &str) {
    return str.find_first_not_of("0123456789") == std::string::npos;
}
