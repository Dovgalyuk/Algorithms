#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "stack.h"

using namespace std;

int fail(Stack* stack, Stack* types, const string& message)
{
    cout << message << '\n';
    stack_delete(types);
    stack_delete(stack);
    return 1;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "NO FILE ARG\n";
        return 1;
    }

    ifstream input(argv[1]);

    if (!input.is_open()) {
        cout << "FILE OPEN ERROR\n";
        return 1;
    }

    int A = 0;
    int B = 0;
    int C = 0;
    int D = 0;

    Stack* stack = stack_create();
    Stack* types = stack_create();

    string command;
    int instructionIndex = 0;

    while (input >> command) {
        if (command == "push") {
            string arg;

            if (!(input >> arg)) {
                return fail(stack, types, "BAD INPUT");
            }

            int value = 0;

            if (arg == "A") {
                value = A;
            }
            else if (arg == "B") {
                value = B;
            }
            else if (arg == "C") {
                value = C;
            }
            else if (arg == "D") {
                value = D;
            }
            else {
                value = atoi(arg.c_str());
            }

            stack_push(stack, value);
            stack_push(types, 0);
        }
        else if (command == "pop") {
            string reg;

            if (!(input >> reg)) {
                return fail(stack, types, "BAD INPUT");
            }

            if (stack_empty(stack)) {
                return fail(stack, types, "BAD POP");
            }

            if (stack_get(types) != 0) {
                return fail(stack, types, "BAD POP");
            }

            int value = stack_get(stack);

            if (reg == "A") {
                A = value;
            }
            else if (reg == "B") {
                B = value;
            }
            else if (reg == "C") {
                C = value;
            }
            else if (reg == "D") {
                D = value;
            }
            else {
                return fail(stack, types, "BAD INPUT");
            }

            stack_pop(stack);
            stack_pop(types);
        }
        else if (command == "add" ||
            command == "sub" ||
            command == "mul") {

            string error = "BAD ADD";

            if (command == "sub") {
                error = "BAD SUB";
            }
            else if (command == "mul") {
                error = "BAD MUL";
            }

            if (stack_empty(stack)) {
                return fail(stack, types, error);
            }

            if (stack_get(types) != 0) {
                return fail(stack, types, error);
            }

            int x = stack_get(stack);
            stack_pop(stack);
            stack_pop(types);

            if (stack_empty(stack)) {
                return fail(stack, types, error);
            }

            if (stack_get(types) != 0) {
                return fail(stack, types, error);
            }

            int y = stack_get(stack);
            stack_pop(stack);
            stack_pop(types);

            int result = 0;

            if (command == "add") {
                result = y + x;
            }
            else if (command == "sub") {
                result = y - x;
            }
            else if (command == "mul") {
                result = y * x;
            }

            stack_push(stack, result);
            stack_push(types, 0);
        }
        else if (command == "call") {
            stack_push(stack, instructionIndex + 1);
            stack_push(types, 1);
        }
        else if (command == "ret") {
            if (stack_empty(stack)) {
                return fail(stack, types, "BAD RET");
            }

            if (stack_get(types) != 1) {
                return fail(stack, types, "BAD RET");
            }

            stack_pop(stack);
            stack_pop(types);
        }
        else {
            return fail(stack, types, "BAD INPUT");
        }

        ++instructionIndex;
    }

    cout << "A = " << A << '\n';
    cout << "B = " << B << '\n';
    cout << "C = " << C << '\n';
    cout << "D = " << D << '\n';

    stack_delete(types);
    stack_delete(stack);

    return 0;
}
