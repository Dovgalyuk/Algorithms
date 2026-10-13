#include <iostream>
#include <fstream>

#include "vector.h"
#include "stack.h"

using namespace std;

struct Interpreter {
    Vector* program;
    Stack* stack[2];
    int currentStack;
    int registerK;
    size_t ip;
};

Interpreter *interpreterCreate(Vector* program) {
    Interpreter* interpreter = new Interpreter;
    interpreter->stack[0] = stack_create();
    interpreter->stack[1] = stack_create();
    interpreter->currentStack = 0;
    interpreter->registerK = 0;
    interpreter->program = program;
    interpreter->ip = 0;
    return interpreter;
}

void interpreterRun(Interpreter *machine) {
    while (machine->ip < vector_size(machine->program)) {

        bool skipIncrement = false;

        int cmd = vector_get(machine->program, machine->ip);

        if (cmd == ' ' || cmd == '\n' || cmd == '\t' || cmd == '\r') {
            machine->ip++;
            continue;
        }
        Stack* ws = machine->stack[machine->currentStack];
        switch (cmd) {
            case 'u':
            case '^':
                if (stack_empty(ws)) {
                    return;
                }
                machine->registerK = stack_get(ws);
                stack_pop(ws);
                break;
            case 'd':
            case 'v':
                stack_push(ws, machine->registerK);
                break;
            case 's':
            case '/': {
                if (stack_empty(ws)) {
                    return;
                }
                int a = stack_get(ws);
                stack_pop(ws);
                if (stack_empty(ws)) {
                    stack_push(ws, a);
                    return;
                }
                int b = stack_get(ws);
                stack_pop(ws);
                stack_push(ws, a);
                stack_push(ws, b);
                break;
            }
            case 'S':
            case ';': {
                machine->currentStack = 1 - machine->currentStack;
                break;
            }
            case 'l':
            case '1':
                stack_push(ws, 1);
                break;
            case 'm':
            case '-': {
                if (stack_empty(ws)) {
                    return;
                }
                int a = stack_get(ws);
                stack_pop(ws);
                if (stack_empty(ws)) {
                    stack_push(ws, a);
                    return;
                }
                int b = stack_get(ws);
                stack_pop(ws);
                stack_push(ws, b - a);
                break;
            }
            case 'i':
            case '[': {
                int num;
                cin >> num;
                stack_push(ws, num);
                break;
            }
            case 'o':
            case ']': {
                if (stack_empty(ws)) {
                    return;
                }
                int num = stack_get(ws);
                stack_pop(ws);
                cout << num;
                break;
            }
            case 'I':
            case '{': {
                char ch;
                cin >> ch;
                stack_push(ws, (int)ch);
                break;
            }
            case 'O':
            case '}': {
                if (stack_empty(ws)) {
                    return;
                }
                int code = stack_get(ws);
                stack_pop(ws);
                cout << (char)code;
                break;
            }
            case 'r':
            case '%': {
                Stack* tempStack = stack_create();
                while (!stack_empty(ws)) {
                    int val = stack_get(ws);
                    stack_pop(ws);
                    stack_push(tempStack, val);
                }
                stack_delete(machine->stack[machine->currentStack]);
                machine->stack[machine->currentStack] = tempStack;
                break;
            }
            case 'f':
            case '*':
                break;
            case 'g':
            case '>': {
                if (stack_empty(ws)) {
                    return;
                }
                int n = stack_get(ws);
                stack_pop(ws);

                if (n == 0) {
                    break;
                }

                if (n > 0) {
                    int count = 0;
                    while (count < n) {
                        machine->ip++;
                        if (machine->ip >= vector_size(machine->program)) {
                            return;
                        }
                        int nextCmd = vector_get(machine->program, machine->ip);
                        if (nextCmd == 'f' || nextCmd == '*') {
                            count++;
                        }
                    }
                } else {
                    int count = 0;
                    int abs_n = -n;
                    while (count < abs_n) {
                        if (machine->ip == 0) {
                            return;
                        }
                        machine->ip--;
                        int nextCmd = vector_get(machine->program, machine->ip);
                        if (nextCmd == 'f' || nextCmd == '*') {
                            count++;
                        }
                    }
                }
                skipIncrement = true;
                break;
            }
            default:
                break;
        }
        if (!skipIncrement) {
            machine->ip++;
        }
    }
}

void interpreterDelete(Interpreter *interpreter) {
    if (interpreter) {
        stack_delete(interpreter->stack[0]);
        stack_delete(interpreter->stack[1]);
        delete interpreter;
    }
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Верный формат: " << argv[0] << " (файлСкрипта.txt) (файлДанных.txt)\n";
        return 1;
    }

    const char* scriptFile = argv[1];
    const char* inputFile = argv[2];

    ifstream script_file(scriptFile);
    if (!script_file) {
        cerr << "Не удалось открыть файл скрипта\n";
        return 1;
    }
    if (freopen(inputFile, "r", stdin) == nullptr) {
        cerr << "Не удалось открыть файл с входными данными: " << inputFile << "\n";
        return 1;
    }

    Vector *programCode = vector_create();
    char ch;
    while (script_file.get(ch)) {
        size_t currentSize = vector_size(programCode);
        vector_resize(programCode, currentSize + 1);
        vector_set(programCode, currentSize, (int)ch);
    }
    script_file.close();

    Interpreter *machine = interpreterCreate(programCode);
    interpreterRun(machine);

    printStack(machine->stack[0]);
    printStack(machine->stack[1]);

    interpreterDelete(machine);
    vector_delete(programCode);

    return 0;
}