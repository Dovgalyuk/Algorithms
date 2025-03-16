#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

#include "stack.h"
using namespace std;

enum DataType {
    DATA_VALUE,
    RETURN_ADDRESS
};

struct StackData {
    Data value;
    DataType type;
};

void stack_push_typed(Stack *stack, Data value, DataType type) {
    StackData data;
    data.value = value;
    data.type = type;
    stack_push(stack, reinterpret_cast<Data&>(data));
}

StackData stack_get_typed(Stack *stack) {
    if (stack_empty(stack)) {
        return {0, DATA_VALUE};
    }
    Data data = stack_get(stack);
    return *reinterpret_cast<StackData*>(&data);
}

StackData stack_pop_typed(Stack *stack) {
    if (stack_empty(stack)) {
        return {0, DATA_VALUE};
    }

    Data rawData = stack_get(stack);
    StackData top_data = *reinterpret_cast<StackData*>(&rawData);
    stack_pop(stack);

    return top_data;
}

string trim(const string& str) {
    string s = str;
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), s.end());
    return s;
}

int main() {
    setlocale(LC_ALL,"Russian");
    Stack *stack = stack_create();
    map<string, int> registers;
    registers["A"] = 0;
    registers["B"] = 0;
    registers["C"] = 0;
    registers["D"] = 0;

    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Ошибка открытия файла: input.txt" << endl;
        stack_delete(stack);
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        line = trim(line);

        if (line.empty()) continue;

        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "push") {
            string operand;
            ss >> operand;
            try {
                int value = stoi(operand);
                stack_push_typed(stack, value, DATA_VALUE);
            } catch (const invalid_argument& e) {
                if (registers.count(operand)) {
                    stack_push_typed(stack, registers[operand], DATA_VALUE);
                } else {
                    cout << "Недействительный регистр" << endl;
                    inputFile.close();
                    stack_delete(stack);
                    return 1;
                }
            }
        } else if (command == "pop") {
            if (stack_empty(stack)) {
                cout << "Пустой стек" << endl;
                inputFile.close();
                stack_delete(stack);
                return 1;
            }

            StackData top_data = stack_pop_typed(stack);
            if (top_data.type == RETURN_ADDRESS) {
                cout << "Не достано число из стека командой - pop" << endl;
                inputFile.close();
                stack_delete(stack);
                return 1;
            }

            string register_name;
            ss >> register_name;
            if (!registers.count(register_name)) {
                cout << "Недействительный регистр." << endl;
                inputFile.close();
                stack_delete(stack);
                return 1;
            }

            registers[register_name] = top_data.value;

        } else if (command == "call") {
            stack_push_typed(stack, -1, RETURN_ADDRESS);
        } else if (command == "ret") {
            if (stack_empty(stack)) {
                cout << "Пустой стек" << endl;
                inputFile.close();
                stack_delete(stack);
                return 1;
            }

            stack_pop_typed(stack);
        } else {
            cout << "Недействительная команда." << endl;
            inputFile.close();
            stack_delete(stack);
            return 1;
        }
    }

    inputFile.close(); 

    cout << "A = " << registers["A"] << endl;
    cout << "B = " << registers["B"] << endl;
    cout << "C = " << registers["C"] << endl;
    cout << "D = " << registers["D"] << endl;

    stack_delete(stack);
    return 0;
}
