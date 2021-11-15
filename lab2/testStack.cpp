#include <iostream>
#include "stack.h"
#include <fstream>
#include <string>

typedef Stack<int> steck;

int main() {
    steck registr;
    int A[1] = {0},
        B[1] = {0},
        C[1] = {0},
        D[1] = {0};

    std::string _string;
    std::ifstream in("E:\\text.txt");

    if(in.is_open()) {
        while (!in.eof()) {
            std::getline(in, _string);
            if (!_string.find("PUSH ")) {
                _string = _string[5];
                if (!_string.find('A'))
                    registr.push(A[0]);
                else if (!_string.find('B'))
                    registr.push(B[0]);
                else if (!_string.find('C'))
                    registr.push(C[0]);
                else if (!_string.find('D'))
                    registr.push(D[0]);
                else
                    registr.push(atoi(_string.c_str()));
            }
            if(registr.empty()) {
                std::cout << "Stack is empty";
                break;
            }
                if (!_string.find("POP")) {
                    _string = _string[4];
                    if (!_string.find('A')) {
                        A[0] = registr.get();
                        registr.pop();
                    } else if (!_string.find('B')) {
                        B[0] = registr.get();
                        registr.pop();
                    } else if (!_string.find('C')) {
                        C[0] = registr.get();
                        registr.pop();
                    } else if (!_string.find('D')) {
                        D[0] = registr.get();
                        registr.pop();
                    } else {
                        std::cout << "Error";
                        in.eof();
                    }
                }
        }
    }
    std::cout << "A = " << *A << std::endl;
    std::cout << "B = " << *B << std::endl;
    std::cout << "C = " << *C << std::endl;
    std::cout << "D = " << *D << std::endl;

    return 0;
}