#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "../LibraryCPP/stack.h"

class JVMStack {
private:
    Stack* stack;
    int variables[4] = {0};
    std::vector<std::string> call_log;

    void check_stack_size(size_t required) {
        if (stack_size(stack) < required) {
            throw std::runtime_error("Stack underflow");
        }
    }

public:
    JVMStack() : stack(stack_create()) {}

    ~JVMStack() { stack_delete(stack); }

    void bipush(int value) {
        call_log.push_back("bipush " + std::to_string(value));
        stack_push(stack, value);
    }

    void pop() {
        call_log.push_back("pop");
        check_stack_size(1);
        stack_pop(stack);
    }

    void imul() {
        call_log.push_back("imul");
        check_stack_size(2);
        int a = stack_get(stack); stack_pop(stack);
        int b = stack_get(stack); stack_pop(stack);
        stack_push(stack, a * b);
    }

    void iand() {
        call_log.push_back("iand");
        check_stack_size(2);
        int a = stack_get(stack); stack_pop(stack);
        int b = stack_get(stack); stack_pop(stack);
        stack_push(stack, a & b);
    }

    void ior() {
        call_log.push_back("ior");
        check_stack_size(2);
        int a = stack_get(stack); stack_pop(stack);
        int b = stack_get(stack); stack_pop(stack);
        stack_push(stack, a | b);
    }

    void ixor() {
        call_log.push_back("ixor");
        check_stack_size(2);
        int a = stack_get(stack); stack_pop(stack);
        int b = stack_get(stack); stack_pop(stack);
        stack_push(stack, a ^ b);
    }

    void iadd() {
        call_log.push_back("iadd");
        check_stack_size(2);
        int a = stack_get(stack); stack_pop(stack);
        int b = stack_get(stack); stack_pop(stack);
        stack_push(stack, a + b);
    }

    void isub() {
        call_log.push_back("isub");
        check_stack_size(2);
        int a = stack_get(stack); stack_pop(stack);
        int b = stack_get(stack); stack_pop(stack);
        stack_push(stack, b - a);
    }

    void iload_0() {
        call_log.push_back("iload_0");
        stack_push(stack, variables[0]);
    }

    void iload_1() {
        call_log.push_back("iload_1");
        stack_push(stack, variables[1]);
    }

    void iload_2() {
        call_log.push_back("iload_2");
        stack_push(stack, variables[2]);
    }

    void iload_3() {
        call_log.push_back("iload_3");
        stack_push(stack, variables[3]);
    }

    void istore_0() {
        call_log.push_back("istore_0");
        check_stack_size(1);
        variables[0] = stack_get(stack);
        stack_pop(stack);
    }

    void istore_1() {
        call_log.push_back("istore_1");
        check_stack_size(1);
        variables[1] = stack_get(stack);
        stack_pop(stack);
    }

    void istore_2() {
        call_log.push_back("istore_2");
        check_stack_size(1);
        variables[2] = stack_get(stack);
        stack_pop(stack);
    }

    void istore_3() {
        call_log.push_back("istore_3");
        check_stack_size(1);
        variables[3] = stack_get(stack);
        stack_pop(stack);
    }

    void swap() {
        call_log.push_back("swap");
        check_stack_size(2);
        int a = stack_get(stack); stack_pop(stack);
        int b = stack_get(stack); stack_pop(stack);
        stack_push(stack, a);
        stack_push(stack, b);
    }

    void invokestatic(int address) {
        call_log.push_back("invokestatic " + std::to_string(address));
        stack_push(stack, -address); // Адрес как отрицательное значение
    }

    void return_op() {
        call_log.push_back("return");
        check_stack_size(1);
        if (stack_get(stack) >= 0) {
            throw std::runtime_error("Return with non-address value");
        }
        stack_pop(stack);
    }

    void print_state() {
        for (const auto& op : call_log) {
            std::cout << op << std::endl;
        }

        std::cout << "stack:" << std::endl;
        if (stack_empty(stack)) {
            std::cout << std::endl;
        } else {
            Stack* temp_stack = stack_create();
            while (!stack_empty(stack)) {
                stack_push(temp_stack, stack_get(stack));
                stack_pop(stack);
            }

            while (!stack_empty(temp_stack)) {
                int val = stack_get(temp_stack);
                std::cout << val << std::endl;
                stack_push(stack, val);
                stack_pop(temp_stack);
            }
            stack_delete(temp_stack);
        }

        std::cout << "vars:" << std::endl;
        for (int var : variables) {
            std::cout << var << std::endl;
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    try {
        JVMStack vm;
        std::ifstream input(argv[1]);
        std::string operation;

        while (input >> operation) {
            if (operation == "bipush") {
                int value;
                input >> value;
                vm.bipush(value);
            } else if (operation == "pop") {
                vm.pop();
            } else if (operation == "imul") {
                vm.imul();
            } else if (operation == "iand") {
                vm.iand();
            } else if (operation == "ior") {
                vm.ior();
            } else if (operation == "ixor") {
                vm.ixor();
            } else if (operation == "iadd") {
                vm.iadd();
            } else if (operation == "isub") {
                vm.isub();
            } else if (operation == "iload_0") {
                vm.iload_0();
            } else if (operation == "iload_1") {
                vm.iload_1();
            } else if (operation == "iload_2") {
                vm.iload_2();
            } else if (operation == "iload_3") {
                vm.iload_3();
            } else if (operation == "istore_0") {
                vm.istore_0();
            } else if (operation == "istore_1") {
                vm.istore_1();
            } else if (operation == "istore_2") {
                vm.istore_2();
            } else if (operation == "istore_3") {
                vm.istore_3();
            } else if (operation == "swap") {
                vm.swap();
            } else if (operation == "invokestatic") {
                int address;
                input >> address;
                vm.invokestatic(address);
            } else if (operation == "return") {
                vm.return_op();
            } else {
                throw std::runtime_error("Unknown operation: " + operation);
            }
        }

        vm.print_state();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}