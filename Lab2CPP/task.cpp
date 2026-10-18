#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <script_file> <input_file>\n";
        return 1;
    }

    std::ifstream script_file(argv[1]);
    if (!script_file.is_open()) {
        std::cerr << "Error opening script file: " << argv[1] << "\n";
        return 1;
    }

    std::ifstream input_file(argv[2]);
    if (!input_file.is_open()) {
        std::cerr << "Error opening input file: " << argv[2] << "\n";
        return 1;
    }

    std::string script((std::istreambuf_iterator<char>(script_file)), std::istreambuf_iterator<char>());
    script_file.close();

    Stack *stack0 = stack_create();
    Stack *stack1 = stack_create();
    Stack *current_stack = stack0;

    Data k = 0;
    size_t ip = 0;

    while (ip < script.length()) {
        char cmd = script[ip];
        
        // Игнорируем пробельные символы
        if (cmd == ' ' || cmd == '\n' || cmd == '\r' || cmd == '\t') {
            ip++;
            continue;
        }

        if (cmd == 'u' || cmd == '^') {
            if (!stack_empty(current_stack)) {
                k = stack_get(current_stack);
                stack_pop(current_stack);
            } else {
                k = 0;
            }
        } else if (cmd == 'd' || cmd == 'v') {
            stack_push(current_stack, k);
        } else if (cmd == 's' || cmd == '/') {
            if (!stack_empty(current_stack)) {
                Data a = stack_get(current_stack);
                stack_pop(current_stack);
                if (!stack_empty(current_stack)) {
                    Data b = stack_get(current_stack);
                    stack_pop(current_stack);
                    stack_push(current_stack, a);
                    stack_push(current_stack, b);
                } else {
                    stack_push(current_stack, a);
                }
            }
        } else if (cmd == 'S' || cmd == ';') {
            current_stack = (current_stack == stack0) ? stack1 : stack0;
        } else if (cmd == 'l' || cmd == '1') {
            stack_push(current_stack, 1);
        } else if (cmd == 'm' || cmd == '-') {
            Data a = 0, b = 0;
            if (!stack_empty(current_stack)) {
                a = stack_get(current_stack);
                stack_pop(current_stack);
            }
            if (!stack_empty(current_stack)) {
                b = stack_get(current_stack);
                stack_pop(current_stack);
            }
            stack_push(current_stack, b - a);
        } else if (cmd == 'i' || cmd == '[') {
            Data val;
            if (input_file >> val) {
                stack_push(current_stack, val);
            } else {
                stack_push(current_stack, 0);
            }
        } else if (cmd == 'o' || cmd == ']') {
            if (!stack_empty(current_stack)) {
                std::cout << stack_get(current_stack) << "\n";
                stack_pop(current_stack);
            }
        } else if (cmd == 'I' || cmd == '{') {
            char ch;
            if (input_file >> ch) {
                stack_push(current_stack, (Data)ch);
            } else {
                stack_push(current_stack, 0);
            }
        } else if (cmd == 'O' || cmd == '}') {
            if (!stack_empty(current_stack)) {
                std::cout << (char)stack_get(current_stack);
                stack_pop(current_stack);
            }
        } else if (cmd == 'r' || cmd == '%') {
            Stack *temp = stack_create();
            while (!stack_empty(current_stack)) {
                stack_push(temp, stack_get(current_stack));
                stack_pop(current_stack);
            }
            while (!stack_empty(temp)) {
                stack_push(current_stack, stack_get(temp));
                stack_pop(temp);
            }
            stack_delete(temp);
        } else if (cmd == 'f' || cmd == '*') {
            // Флаг, ничего не делает
        } else if (cmd == 'g' || cmd == '>') {
            Data n = 0;
            if (!stack_empty(current_stack)) {
                n = stack_get(current_stack);
                stack_pop(current_stack);
            }
            if (n > 0) {
                int count = 0;
                for (size_t i = ip + 1; i < script.length(); ++i) {
                    if (script[i] == '*' || script[i] == 'f') {
                        count++;
                        if (count == n) {
                            ip = i;
                            break;
                        }
                    }
                }
            } else if (n < 0) {
                int count = 0;
                int target = -n;
                for (int i = (int)ip - 1; i >= 0; --i) {
                    if (script[i] == '*' || script[i] == 'f') {
                        count++;
                        if (count == target) {
                            ip = i;
                            break;
                        }
                    }
                }
            }
        }

        ip++;
    }

    // Вывод состояния стеков (снизу вверх)
    Stack *temp0 = stack_create();
    while (!stack_empty(stack0)) {
        stack_push(temp0, stack_get(stack0));
        stack_pop(stack0);
    }
    bool first = true;
    while (!stack_empty(temp0)) {
        if (!first) std::cout << " ";
        std::cout << stack_get(temp0);
        stack_pop(temp0);
        first = false;
    }
    std::cout << "\n";
    stack_delete(temp0);

    Stack *temp1 = stack_create();
    while (!stack_empty(stack1)) {
        stack_push(temp1, stack_get(stack1));
        stack_pop(stack1);
    }
    first = true;
    while (!stack_empty(temp1)) {
        if (!first) std::cout << " ";
        std::cout << stack_get(temp1);
        stack_pop(temp1);
        first = false;
    }
    std::cout << "\n";
    stack_delete(temp1);

    stack_delete(stack0);
    stack_delete(stack1);

    return 0;
}