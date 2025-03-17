#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cctype>     // Для isdigit()
#include <algorithm>  // Для find_if()
#include "stack.h"

using namespace std;

class CPU {
private:
    Stack* stack;
    unordered_map<string, int> registers;
    bool error = false;
    int returnCount = 0; // Счетчик адресов возврата

public:
    CPU() {
        stack = stack_create();
    }

    ~CPU() {
        stack_delete(stack);
    }

    // Проверка, является ли строка числом (включая отрицательные)
    bool isNumber(const string& str) {
        if (str.empty()) return false;
        if (str[0] == '-' && str.size() > 1) { // Отрицательные числа
            return all_of(str.begin() + 1, str.end(), ::isdigit);
        }
        return all_of(str.begin(), str.end(), ::isdigit);
    }

    void push(const string& operand) {
        if (isNumber(operand)) { // Проверяем, является ли строка числом
            stack_push(stack, stoi(operand));
        } else {
            stack_push(stack, registers[operand]);
        }
    }

    void pop(const string& reg) {
        if (stack_empty(stack)) {
            cout << "ERROR: Stack underflow" << endl;
            error = true;
            return;
        }
        if (returnCount > 0) { // Нельзя изменять стек, если там есть адрес возврата
            cout << "ERROR: Cannot pop return address" << endl;
            error = true;
            return;
        }
        registers[reg] = stack_get(stack);
        stack_pop(stack);
    }

    void add() { operate('+'); }
    void sub() { operate('-'); }
    void mul() { operate('*'); }

    void call() {
        stack_push(stack, -2); // Специальный маркер адреса возврата
        returnCount++;
    }

    void ret() {
        if (returnCount == 0) {
            cout << "ERROR: Nothing to return to" << endl;
            error = true;
            return;
        }
        while (!stack_empty(stack)) { // Удаляем все адреса возврата
            int value = stack_get(stack);
            stack_pop(stack);
            if (value == -2) { // Нашли метку возврата
                returnCount--;
                if (returnCount == 0) break; // Все возвраты обработаны
            }
        }
    }

    void print_registers() {
        if (!error) {
            for (const auto& reg : registers) {
                cout << reg.first << " = " << reg.second << endl;
            }
        }
    }

private:
    void operate(char op) {
        if (stack_size(stack) < 2) {
            cout << "ERROR: Stack underflow" << endl;
            error = true;
            return;
        }
        int b = stack_get(stack);
        stack_pop(stack);
        int a = stack_get(stack);
        stack_pop(stack);

        switch (op) {
            case '+': stack_push(stack, a + b); break;
            case '-': stack_push(stack, a - b); break;
            case '*': stack_push(stack, a * b); break;
        }
    }
};

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    istream* input = &cin;
    ifstream inputFile;
    if (argc >= 2) {
        inputFile.open(argv[1]);
        if (!inputFile) {
            cerr << "Ошибка: не удалось открыть файл " << argv[1] << endl;
            return 1;
        }
        input = &inputFile;
    }

    CPU cpu;
    string command;
    while (*input >> command) {
        if (command == "push") {
            string operand;
            *input >> operand;
            cpu.push(operand);
        } else if (command == "pop") {
            string reg;
            *input >> reg;
            cpu.pop(reg);
        } else if (command == "add") {
            cpu.add();
        } else if (command == "sub") {
            cpu.sub();
        } else if (command == "mul") {
            cpu.mul();
        } else if (command == "call") {
            cpu.call();
        } else if (command == "ret") {
            cpu.ret();
        } else {
            cout << "ERROR: Unknown command " << command << endl;
            return 1;
        }
    }
    cpu.print_registers();
    return 0;
}
