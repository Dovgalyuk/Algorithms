#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "stack.h"

using namespace std;

void error(const string& msg) {
    cerr << "Ошибка: " << msg << endl;
    exit(1);
}

static Stack* data_stack; // для хранения чисел и адресов
static Stack* kind_stack; // для маркера 0 - число, 1 - адрес возврата

static void push_val(int v) {
    stack_push(data_stack, v);
    stack_push(kind_stack, 0);
}

static void push_addr(int v) {
    stack_push(data_stack, v);
    stack_push(kind_stack, 1);
}

static int pop_val(const string& op) {
    if (stack_empty(data_stack))
        error("переполнение стека (stack underflow) в команде " + op);
    if (stack_get(kind_stack) == 1)
        error(op + ": нельзя использовать адрес возврата как обычное значение");
    int v = stack_get(data_stack);
    stack_pop(data_stack);
    stack_pop(kind_stack);
    return v;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Использование: " << argv[0] << " <входной_файл>" << endl;
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin.is_open()) {
        cerr << "Не удалось открыть файл: " << argv[1] << endl;
        return 1;
    }

    vector<string> lines;
    string line;
    while (getline(fin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();//Проверка на случай, если файл был создан в Windows и содержат /r
        lines.push_back(line);
    }
    fin.close();

    data_stack = stack_create();
    kind_stack = stack_create();

    int vars[4] = {0, 0, 0, 0};
    int pc = 0;
    int n = lines.size();

    const int MAX_ITERATIONS = 100000;
    int iterations = 0;

    while (pc < n) {
        iterations++;
        if (iterations > MAX_ITERATIONS) {
            error("Обнаружен бесконечный цикл");
        }

        const string& cmd = lines[pc];
        if (cmd.empty()) {
            pc++;
            continue;ф
        }

        istringstream iss(cmd); //Позволяет работать со строкой как с потоком cin
        string op;
        iss >> op; //Разбивает строку до первого пробела и записывает в op

        if (op == "bipush") {
            int val;
            if (!(iss >> val))
                error("команда bipush требует целое число");
            push_val(val);
        }
        else if (op == "pop") {
            if (stack_empty(data_stack))
                error("переполнение стека в команде pop");
            if (stack_get(kind_stack) == 1)
                error("нельзя удалять адрес возврата командой pop");
            stack_pop(data_stack);
            stack_pop(kind_stack);
        }
        else if (op == "imul" || op == "iand" || op == "ior" || op == "ixor" || op == "iadd" || op == "isub") {
            int b = pop_val(op);
            int a = pop_val(op);

            unsigned ua = (unsigned)a, ub = (unsigned)b;
            int r = 0;
            if (op == "imul") r = (int)(ua * ub);
            else if (op == "iand") r = a & b;
            else if (op == "ior")  r = a | b;
            else if (op == "ixor") r = a ^ b;
            else if (op == "iadd") r = (int)(ua + ub);
            else if (op == "isub") r = (int)(ua - ub);
            push_val(r);
        }
        else if (op == "iload_0" || op == "iload_1" || op == "iload_2" || op == "iload_3") {
            int idx = op.back() - '0';
            push_val(vars[idx]);
        }
        else if (op == "istore_0" || op == "istore_1" || op == "istore_2" || op == "istore_3") {
            int idx = op.back() - '0';
            vars[idx] = pop_val(op);
        }
        else if (op == "swap") {
            if (stack_empty(data_stack))
                error("переполнение стека в команде swap");
            int a = stack_get(data_stack);
            int ka = stack_get(kind_stack);
            stack_pop(data_stack);
            stack_pop(kind_stack);

            if (stack_empty(data_stack))
                error("переполнение стека в команде swap");
            int b = stack_get(data_stack);
            int kb = stack_get(kind_stack);
            stack_pop(data_stack);
            stack_pop(kind_stack);

            stack_push(data_stack, b);
            stack_push(kind_stack, kb);
            stack_push(data_stack, a);
            stack_push(kind_stack, ka);
        }
        else if (op == "invokestatic") {
            int addr;
            if (!(iss >> addr))
                error("команда invokestatic требует адрес");
            if (addr < 1 || addr > n)
                error("некорректный адрес вызова: " + to_string(addr));

            push_addr(pc + 1);
            cout << "call " << addr << endl;
            pc = addr - 1;
            continue;
        }
        else if (op == "return") {
            if (stack_empty(data_stack)) {
                error("return: стек пуст");
            }
            if (stack_get(kind_stack) != 1) {
                error("return: на вершине стека не адрес возврата");
            }
            int ret_addr = stack_get(data_stack);
            stack_pop(data_stack);
            stack_pop(kind_stack);
            pc = ret_addr;
            continue; //!!!!!!
        }
        else {
            error("неизвестная команда: " + op);
        }

        pc++;
    }

    cout << "stack:" << endl;
    Stack* temp_data = stack_create();
    Stack* temp_kind = stack_create();

    while (!stack_empty(data_stack)) {
        stack_push(temp_data, stack_get(data_stack));
        stack_push(temp_kind, stack_get(kind_stack));
        stack_pop(data_stack);
        stack_pop(kind_stack);
    }

    while (!stack_empty(temp_data)) {
        int val = stack_get(temp_data);
        int kind = stack_get(temp_kind);
        if (kind == 0) {
            cout << val << endl;
        }
        stack_push(data_stack, val);
        stack_push(kind_stack, kind);
        stack_pop(temp_data);
        stack_pop(temp_kind);
    }

    stack_delete(temp_data);
    stack_delete(temp_kind);

    cout << "vars:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << vars[i] << endl;
    }

    stack_delete(data_stack);
    stack_delete(kind_stack);
    return 0;
}