#include <iostream>
#include "array.h"
#include "stack.h"
#include <string>

const std::string PUSH = "PUSH";
const std::string POP = "POP";
const char NUMBERS = '0';
const char SYMBOLS = 'A';

int main(){
    Stack* stack = stack_create();
    Array* processor = array_create(4);
    for (size_t i = 0; i < 4; i++) array_set(processor, i, 0);
    
    std::string _register;
    char number;
    std::cout << "Input 'STOP STOP' for stop the programm\n";

    do
    {
        std::cout << "Input command: ";
        std::cin >> _register >> number;
        if ((_register == PUSH || _register == POP) && (number >= '0' && number <= '9') || (number >= 'A' && number <= 'D')) {
            if (_register == PUSH) {
                if (number >= '0' && number <= '9') { stack_push(stack, number - NUMBERS); }
                else if (number >= 'A' && number <= 'D') {
                    int index = number - SYMBOLS;
                    if (array_get(processor, index) != 0) { stack_push(stack, array_get(processor, index)); }
                    else std::cout << "Register is empty\n";
                }
            }
            else if (_register == POP) {
                if (!stack_empty(stack)) {
                    int index = number - SYMBOLS;
                    array_set(processor, index, stack_get(stack));
                    stack_pop(stack);
                }
                else std::cout << "Stack empty!\n";
            }
        }
        else if (_register != "STOP") std::cout << "unknown command\n";
    } while ((number >= '0' && number <= '9') || (number >= 'A' && number <= 'D') || _register != "STOP");

    std::cout << "\n";
    for (size_t i = 0; i < 4; i++) std::cout << char(SYMBOLS + i) << " = " << array_get(processor, i) << "\n";

    return 0;
}