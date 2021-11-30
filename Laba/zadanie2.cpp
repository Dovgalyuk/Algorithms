#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "stack.h"

int main() {

    Stack *stack = stack_create();

    int A = 0, B = 0, C = 0, D = 0;

    std::string str;

    std::ifstream file("C:\\Algorithms\\LibraryCPP\\file.txt");

    if (file.is_open()) {

        while (!file.eof()) {
            std::getline(file, str);

            if (!str.find("PUSH ")) {
                // str = str[5];
                str = str.substr(5);

                if (!str.find('A')) {
                    stack_push(stack, A);
                }
                else if (!str.find('B')) {
                    stack_push(stack, B);
                }
                else if (!str.find('C')) {
                    stack_push(stack, C);
                }
                else if (!str.find('D')) {
                    stack_push(stack, D);
                }
                else {
                    stack_push(stack, std::stoi(str));
                }
            }

            if (stack_empty(stack)) {
                std::cout << "Empty Stack";
                break;
            }
            else if (!str.find("POP ")) {
                str = str[4];

                if (!str.find('A')) {
                    A = stack_get(stack);
                    stack_pop(stack);
                }
                else if (!str.find('B')) {
                    B = stack_get(stack);
                    stack_pop(stack);
                }
                else if (!str.find('C')) {
                    C = stack_get(stack);
                    stack_pop(stack);
                }
                else if (!str.find('D')) {
                    D = stack_get(stack);
                    stack_pop(stack);
                }
                else {
                    std::cout << "error" << std::endl;
                    file.eof();
                }
            }
        }
    }
    else {
        std::cout << "Error opening file" << std::endl;
    }

    std::cout << "A = " << A << std::endl << "B = " << B << std::endl << "C = " << C << std::endl << "D = " << D << std::endl;

    stack_delete(stack);

    return 0;
}