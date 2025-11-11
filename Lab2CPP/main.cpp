#include "stack.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>

class BefungeInterpreter {
private:
    Stack* stack;
    
public:
    BefungeInterpreter() {
        stack = stack_create();
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }
    
    ~BefungeInterpreter() {
        stack_delete(stack);
    }
    
    void execute(const std::string& program) {
        for (char c : program) {
            switch (c) {
                case '0': case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8': case '9':
                    stack_push(stack, c - '0');
                    break;
                    
                case '+': {
                    if (stack_empty(stack)) break;
                    Data a = stack_get(stack); stack_pop(stack);
                    if (stack_empty(stack)) break;
                    Data b = stack_get(stack); stack_pop(stack);
                    stack_push(stack, a + b);
                    break;
                }
                    
                case '-': {
                    if (stack_empty(stack)) break;
                    Data a = stack_get(stack); stack_pop(stack);
                    if (stack_empty(stack)) break;
                    Data b = stack_get(stack); stack_pop(stack);
                    stack_push(stack, b - a);
                    break;
                }
                    
                case '*': {
                    if (stack_empty(stack)) break;
                    Data a = stack_get(stack); stack_pop(stack);
                    if (stack_empty(stack)) break;
                    Data b = stack_get(stack); stack_pop(stack);
                    stack_push(stack, a * b);
                    break;
                }
                    
                case '/': {
                    if (stack_empty(stack)) break;
                    Data a = stack_get(stack); stack_pop(stack);
                    if (stack_empty(stack) || a == 0) break;
                    Data b = stack_get(stack); stack_pop(stack);
                    stack_push(stack, b / a);
                    break;
                }
                    
                case '%': {
                    if (stack_empty(stack)) break;
                    Data a = stack_get(stack); stack_pop(stack);
                    if (stack_empty(stack) || a == 0) break;
                    Data b = stack_get(stack); stack_pop(stack);
                    stack_push(stack, b % a);
                    break;
                }
                    
                case '!': {
                    if (stack_empty(stack)) break;
                    Data a = stack_get(stack); stack_pop(stack);
                    stack_push(stack, a == 0 ? 1 : 0);
                    break;
                }
                    
                case '`': {
                    if (stack_empty(stack)) break;
                    Data a = stack_get(stack); stack_pop(stack);
                    if (stack_empty(stack)) break;
                    Data b = stack_get(stack); stack_pop(stack);
                    stack_push(stack, b > a ? 1 : 0);
                    break;
                }
                    
                case ':': {
                    if (stack_empty(stack)) break;
                    Data a = stack_get(stack);
                    stack_push(stack, a);
                    break;
                }
                    
                case '.': {
                    if (stack_empty(stack)) break;
                    Data a = stack_get(stack); stack_pop(stack);
                    std::cout << a << "\n";
                    break;
                }
                    
                case '&': {
                    stack_push(stack, std::rand() % 100);
                    break;
                }
                    
                default:
                    // Ignore unknown characters
                    break;
            }
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <program_string_or_file>" << std::endl;
        return 1;
    }
    
    std::string program;
    std::string arg = argv[1];
    
    std::ifstream file(arg);
    if (file.is_open()) {
        std::getline(file, program);
        file.close();
    } else {
        program = arg;
    }
    
    BefungeInterpreter interpreter;
    interpreter.execute(program);
    
    return 0;
}