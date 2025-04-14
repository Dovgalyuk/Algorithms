#include <iostream>      // для cout и cin
#include <fstream>       // для работы с файлами
#include <string>        // для строк
#include <unordered_map> // для хранения регистров
#include <cctype>        // для проверки символов
#include <algorithm>     // для алгоритмов, тут не обязательно
#include "stack.h"       // наш модуль стека, мы его сами писали!

// Стек — это структура данных, которая работает по принципу 
// «последний пришёл — первый ушёл» (Last In — First Out, LIFO).
/*
У нас есть класс CPU, который имитирует процессор.

Внутри него:

    стек (Stack* stack) — наша стопка тарелок;

    регистры (unordered_map<string, int> registers) — как ячейки памяти для хранения чисел;

    обработка ошибок (bool error).
*/
using namespace std;

const int RETURN_MARKER = -2; // Специальный маркер для call/ret

class CPU {
private:
    Stack* stack;
    unordered_map<string, int> registers;
    bool error = false;

public:
    // Конструктор и деструктор
    // Когда создаётся процессор, мы создаём пустой стек.
    CPU() {
        stack = stack_create(); // создаём стек
    }
    // Когда процессор уничтожается, мы освобождаем память.
    ~CPU() {
        stack_delete(stack); // очищаем стек при выходе
    }

    // Проверяет, является ли переданная строка числом. (включая отрицательные)
    // Также она специально запрещает использовать число -2, 
    // потому что у нас есть служебное значение RETURN_MARKER = -2. Оно нужно для управления возвратами.
    bool isNumber(const string& str) {
        if (str.empty()) return false;
        int value = 0;
        try {
            size_t idx;
            value = stoi(str, &idx);
            if (idx != str.size()) return false; // проверяем, что вся строка — число
        } catch (...) {
            return false;
        }
        if (value == RETURN_MARKER) return false;
        return true;
    }

    // Команда PUSH Кладёт число или значение из регистра в стек.
    /*Как работает:

    Если operand — это число, мы кладём его в стек.

    Если это имя регистра (например, "A"), мы берём значение из регистра и кладём в стек. */
    void push(const string& operand) {
        if (isNumber(operand)) {
            int value = stoi(operand);
            if (value == RETURN_MARKER) {
                cout << "ERROR: Invalid push value (-2 is reserved)" << endl;
                error = true;
                return;
            }
            stack_push(stack, value); // кладем число в стек
        } else {
            stack_push(stack, registers[operand]); // кладем значение регистра
        }
    }   
    
    // Команда POP Достаёт верхнее значение из стека и кладёт в регистр.
    /*Как работает:

    Проверяет, не пустой ли стек.

    Если всё ок, берёт верхнее значение и кладёт в регистр с именем reg.*/
    void pop(const string& reg) {
        if (stack_empty(stack)) {
            cout << "ERROR: Stack underflow" << endl;
            error = true;
            return;
        }
        registers[reg] = stack_get(stack); // снимаем верхнее значение стека и кладём в регистр
        stack_pop(stack); // убираем верхнее значение стека
    }
    
    // Арифметические операции Просто вызывают operate() с нужной операцией.
    void add() { operate('+'); }
    void sub() { operate('-'); }
    void mul() { operate('*'); }

    // Команда CALL Эмулирует вызов подпрограммы.
    /*Как работает:

    Сначала кладёт в стек специальный маркер возврата (RETURN_MARKER = -2), чтобы потом ret() знал, что за ним лежит адрес возврата.

    Затем кладёт в стек адрес возврата.

Это как если бы ты вызвал функцию: процессор запоминает, куда вернуться после вызова.*/
    void call(int returnAddress) {
        stack_push(stack, RETURN_MARKER); // Добавляем маркер перед адресом возврата
        stack_push(stack, returnAddress);
    }
    // Команда RET Возвращает адрес, куда нужно прыгнуть после вызова подпрограммы.
    /*Как работает:

    Проверяет, не пустой ли стек.

    Проверяет, лежит ли на вершине стека маркер возврата.

    Затем берёт адрес возврата и возвращает его.

Если порядок неверный, например, в стеке вместо маркера возврата лежит число из push, то выводится ошибка.*/
    int ret() {
        if (stack_empty(stack)) {
            cout << "ERROR: Nothing to return to" << endl;
            error = true;
            return -1;
        }

        int value = stack_get(stack);
        stack_pop(stack);

        if (value != RETURN_MARKER) {
            cout << "ERROR: Invalid return sequence" << endl;
            error = true;
            return -1;
        }

        if (stack_empty(stack)) {
            cout << "ERROR: Stack corrupted, missing return address" << endl;
            error = true;
            return -1;
        }

        int returnAddress = stack_get(stack);
        stack_pop(stack);
        return returnAddress;
    }

    // Печать регистров Выводит содержимое всех регистров, если не было ошибок.
    void print_registers() {
        if (!error) {
            for (const auto& reg : registers) {
                cout << reg.first << " = " << reg.second << endl;
            }
        }
    }

private:
    // Все три команды работают через одну вспомогательную функцию: Выполняет операции сложения, вычитания или умножения.
    /*Как работает:

    Достаёт два верхних значения из стека.

    Выполняет операцию:

        '+' — сложение

        '-' — вычитание

        '*' — умножение

    Результат кладёт обратно в стек.*/
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

/*Читаем команды из файла или с клавиатуры.

Для каждой команды вызываем соответствующую функцию процессора:

    push X — кладём значение или регистр в стек.

    pop X — достаём значение из стека в регистр.

    add / sub / mul — выполняем операцию.

    call — кладём адрес возврата в стек.

    ret — возвращаемся по сохранённому адресу.

После выполнения всех команд печатаем содержимое регистров.*/
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
    int programCounter = 0;
    unordered_map<int, int> callStack;

    while (*input >> command) {
        programCounter++;

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
            callStack[programCounter] = programCounter;
            cpu.call(programCounter);
        } else if (command == "ret") {
            int returnAddress = cpu.ret();
            if (returnAddress != -1) {
                programCounter = returnAddress;
            }
        } else {
            cout << "ERROR: Unknown command " << command << endl;
            return 1;
        }
    }

    cpu.print_registers();
    return 0;
}
