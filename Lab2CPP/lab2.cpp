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
    std::vector<bool> is_return_address_stack;

    void check_stack_size(size_t required) {
        if (stack_size(stack) < required) {
            throw std::runtime_error("Stack underflow");
        }
    }

    void check_return_address() {
        if (!is_return_address_stack.empty() && is_return_address_stack.back()) {
            throw std::runtime_error("Invalid operation with return address");
        }
    }

public:
    JVMStack() : stack(stack_create()) {}

    ~JVMStack() { stack_delete(stack); }

    //помещает значение в стек
    void bipush(int value) {
        call_log.push_back("bipush " + std::to_string(value));
        stack_push(stack, value);
        is_return_address_stack.push_back(false);
    }

    //удаление верхнего элемента стека
    void pop() {
        call_log.push_back("pop");
        check_stack_size(1);
        check_return_address();
        stack_pop(stack);
        is_return_address_stack.pop_back();
    }

    //Умножение 
    void imul() {
        call_log.push_back("imul");
        check_stack_size(2);
        check_return_address();
        int a = stack_get(stack); stack_pop(stack); is_return_address_stack.pop_back();
        int b = stack_get(stack); stack_pop(stack); is_return_address_stack.pop_back();
        stack_push(stack, a * b); is_return_address_stack.push_back(false);
    }

    //И
    void iand() {
        call_log.push_back("iand");
        check_stack_size(2);
        check_return_address();
        int a = stack_get(stack); stack_pop(stack); is_return_address_stack.pop_back();
        int b = stack_get(stack); stack_pop(stack); is_return_address_stack.pop_back();
        stack_push(stack, a & b); is_return_address_stack.push_back(false);
    }

    //ИЛИ
    void ior() {
        call_log.push_back("ior");
        check_stack_size(2);
        check_return_address();
        int a = stack_get(stack); stack_pop(stack); is_return_address_stack.pop_back();
        int b = stack_get(stack); stack_pop(stack); is_return_address_stack.pop_back();
        stack_push(stack, a | b); is_return_address_stack.push_back(false);
    }

    //исключающее ИЛИ
    void ixor() {
        call_log.push_back("ixor");
        check_stack_size(2);
        check_return_address();
        int a = stack_get(stack); stack_pop(stack); is_return_address_stack.pop_back();
        int b = stack_get(stack); stack_pop(stack); is_return_address_stack.pop_back();
        stack_push(stack, a ^ b); is_return_address_stack.push_back(false);
    }

    //Сложение 
    void iadd() {
        call_log.push_back("iadd");
        check_stack_size(2);
        check_return_address();
        int a = stack_get(stack); stack_pop(stack); is_return_address_stack.pop_back();
        int b = stack_get(stack); stack_pop(stack); is_return_address_stack.pop_back();
        stack_push(stack, a + b); is_return_address_stack.push_back(false);
    }

    //Вычитание
    void isub() {
        call_log.push_back("isub");
        check_stack_size(2);
        check_return_address();
        int a = stack_get(stack); stack_pop(stack); is_return_address_stack.pop_back();
        int b = stack_get(stack); stack_pop(stack); is_return_address_stack.pop_back();
        stack_push(stack, b - a); is_return_address_stack.push_back(false);
    }

    //загружают локальную переменную из variables[i] в стек
    void iload_0() {
        call_log.push_back("iload_0");
        stack_push(stack, variables[0]);
        is_return_address_stack.push_back(false);
    }

    void iload_1() {
        call_log.push_back("iload_1");
        stack_push(stack, variables[1]);
        is_return_address_stack.push_back(false);
    }

    void iload_2() {
        call_log.push_back("iload_2");
        stack_push(stack, variables[2]);
        is_return_address_stack.push_back(false);
    }

    void iload_3() {
        call_log.push_back("iload_3");
        stack_push(stack, variables[3]);
        is_return_address_stack.push_back(false);
    }

    //Cохранение в переменную variables[i]
    void istore_0() {
        call_log.push_back("istore_0");
        check_stack_size(1);
        check_return_address();
        variables[0] = stack_get(stack);
        stack_pop(stack);
        is_return_address_stack.pop_back();
    }

    void istore_1() {
        call_log.push_back("istore_1");
        check_stack_size(1);
        check_return_address();
        variables[1] = stack_get(stack);
        stack_pop(stack);
        is_return_address_stack.pop_back();
    }

    void istore_2() {
        call_log.push_back("istore_2");
        check_stack_size(1);
        check_return_address();
        variables[2] = stack_get(stack);
        stack_pop(stack);
        is_return_address_stack.pop_back();
    }

    void istore_3() {
        call_log.push_back("istore_3");
        check_stack_size(1);
        check_return_address();
        variables[3] = stack_get(stack);
        stack_pop(stack);
        is_return_address_stack.pop_back();
    }

    //меняет местами два верхних значения стека
    void swap() {
        call_log.push_back("swap");
        check_stack_size(2);
        check_return_address();
        int a = stack_get(stack); stack_pop(stack); bool a_flag = is_return_address_stack.back(); is_return_address_stack.pop_back();
        int b = stack_get(stack); stack_pop(stack); bool b_flag = is_return_address_stack.back(); is_return_address_stack.pop_back();
        stack_push(stack, a); is_return_address_stack.push_back(b_flag);
        stack_push(stack, b); is_return_address_stack.push_back(a_flag);
    }

    //кладёт в стек адрес возврата
    void invokestatic(int address) {
        call_log.push_back("invokestatic " + std::to_string(address));
        stack_push(stack, -address);
        is_return_address_stack.push_back(true);
    }

    //снимает адрес возврата
    void return_op() {
        call_log.push_back("return");
        check_stack_size(1);
        if (!is_return_address_stack.back()) {
            throw std::runtime_error("Return with non-address value");
        }
        stack_pop(stack);
        is_return_address_stack.pop_back();
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
            std::vector<bool> temp_flags;

            while (!stack_empty(stack)) {
                int val = stack_get(stack);
                stack_pop(stack);
                stack_push(temp_stack, val);
                temp_flags.push_back(is_return_address_stack.back());
                is_return_address_stack.pop_back();
            }

            for (int i = temp_flags.size() - 1; i >= 0; --i) {
                int val = stack_get(temp_stack);
                std::cout << val << std::endl;
                stack_pop(temp_stack);
                stack_push(stack, val);
                is_return_address_stack.push_back(temp_flags[i]);
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