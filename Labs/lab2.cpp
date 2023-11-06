#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "stack.h"
#include "vector.h"

using namespace std;

int main() {
    string filename = "input.txt";
    Stack* stack = stack_create();
    Vector* strings = vector_create();
    Vector* registers = vector_create();
    vector_resize(strings, 4);
    vector_resize(registers, 4);

    vector_set(registers, 0, 0);
    vector_set(registers, 1, 0);
    vector_set(registers, 2, 0);
    vector_set(registers, 3, 0);

    vector_set(strings, 0, 'A');
    vector_set(strings, 1, 'B');
    vector_set(strings, 2, 'C');
    vector_set(strings, 3, 'D');

    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Failed to open input file." << endl;
        return 0;
    }

    string line;
    while (getline(inputFile, line)) {
        char param;
        int value;

        if (line.empty()) {
            continue;
        }

        if (line.substr(0, 4) == "PUSH") {
            stringstream ss(line.substr(5));
            if (isalpha(ss.peek())) {
                ss >> param;
                for (int i = 0; i < 4; i++) if (param == vector_get(strings, i)) param = i;
                value = vector_get(registers, param);
            }
            else {
                ss >> value;
            }
            stack_push(stack, value);
        }
        else if (line.substr(0, 3) == "POP") {
            stringstream ss(line.substr(4));
            ss >> param;
            for (int i = 0; i < 4; i++) if (param == vector_get(strings, i)) param = i;
            value = stack_get(stack);
            stack_pop(stack);
            vector_set(registers, param, value);
        }
        else {
            cerr << "Invalid operation: " << line << endl;
            return 0;
        }
    }

    inputFile.close();
    stack_delete(stack);
    for (int i = 0; i < 4; i++) cout << vector_get(strings, i) << " = " << vector_get(registers, i) << endl;
    return 0;
}
