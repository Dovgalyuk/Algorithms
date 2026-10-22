#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

using namespace std;

static bool is_opening(char c) {
    const char symbols[4] = {'(', '[', '<', '{'};

    for (char symbol : symbols) {
        if (symbol == c) {
            return true;
        }
    }

    return false;
}

static bool is_matching(char open, char close) {
    const char opening[4] = {'(', '[', '<', '{'};
    const char closing[4] = {')', ']', '>', '}'};

    for (int i = 0; i < 4; i++) {
        if (opening[i] == open && closing[i] == close) {
            return true;
        }
    }

    return false;
}

static bool check_brackets(const char* str) {
    Stack* stack = stack_create();

    for (int i = 0; str[i] != '\0'; i++) {
        if (is_opening(str[i])) {
            stack_push(stack, str[i]);
        } else {
            if (stack_empty(stack)) {
                stack_delete(stack);
                return false;
            }

            char open = static_cast<char>(stack_get(stack));
            stack_pop(stack);

            if (!is_matching(open, str[i])) {
                stack_delete(stack);
                return false;
            }
        }
    }

    if (!stack_empty(stack)) {
        stack_delete(stack);
        return false;
    }

    stack_delete(stack);
    return true;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input> [output]" << endl;
        return 1;
    }

    ifstream in(argv[1]);

    if (!in) {
        cerr << "Cannot open input file" << endl;
        return 1;
    }

    string str;
    in >> str;

    const char* answer = check_brackets(str.c_str()) ? "YES" : "NO";

    if (argc >= 3) {
        ofstream out(argv[2]);

        if (!out) {
            cerr << "Cannot open output file" << endl;
            return 1;
        }

        out << answer << endl;
    } else {
        cout << answer << endl;
    }

    return 0;
}