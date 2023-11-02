#include <iostream>
#include "stack.h"
#include <cctype> // Для isdigit
#include <string>

using namespace std;

int main() {
    Stack* stack = stack_create();
    int registers[4] = { 0 }; // Массив для хранения значений регистров

    cout << "Enter PUSH or POP (enter x to exit):" << endl;

    while (true) {
        string operation;
        cin >> operation;

        if (operation == "x") {
            break; // Выход из цикла при вводе 'q'
        }
        else if (operation == "PUSH") {
            string param;
            cin >> param;

            if (param == "A") {
                stack_push(stack, registers[0]);
            }
            else if (param == "B") {
                stack_push(stack, registers[1]);
            }
            else if (param == "C") {
                stack_push(stack, registers[2]);
            }
            else if (param == "D") {
                stack_push(stack, registers[3]);
            }
            else if (param.length() == 1 && isdigit(param[0])) {
                Data data = stoi(param);
                stack_push(stack, data);
            }
            else {
                cout << "PUSH operator is incorrect" << param << endl;
            }
        }
        else if (operation == "POP") {
            char reg;
            cin >> reg;
            Data value = stack_get(stack);
            cout << reg << " = " << value << endl;

            if (reg == 'A') {
                registers[0] = value;
            }
            else if (reg == 'B') {
                registers[1] = value;
            }
            else if (reg == 'C') {
                registers[2] = value;
            }
            else if (reg == 'D') {
                registers[3] = value;
            }

            stack_pop(stack);
        }
    }

    cout << "A = " << registers[0] << endl;
    cout << "B = " << registers[1] << endl;
    cout << "C = " << registers[2] << endl;
    cout << "D = " << registers[3] << endl;

    stack_delete(stack);
    return 0;
}
