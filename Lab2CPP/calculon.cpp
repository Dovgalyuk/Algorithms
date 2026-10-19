#include <iostream>
#include <fstream>
#include "stack.h"
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

bool skip_after_cond_to_end(ifstream &script) {
    int depth = 1;
    string word;
    while (script >> word) {
        if (word == "cond") {
            depth += 1;
        } else if (word == "end") {
            depth -= 1;
            if (depth == 0) {
                return true;
            }
        }
    }
    return false;
}

bool parse_number(const string &word, Data &value) {
    try {
        size_t used = 0;
        value = stod(word, &used);
        return used == word.size();
    } catch (...) {
        return false;
    }
}

bool pop_value(Stack *stack, Data &value) {
    if (stack_empty(stack)) {
        return false;
    }
    value = stack_get(stack);
    stack_pop(stack);
    return true;
}

void print(Data value) {
    if (isnan(value)) {
        cout << "nan";
    } else if (isinf(value)) {
        cout << (value > 0 ? "inf" : "-inf");
    } else if (value == floor(value) && fabs(value) < 1e15) {
        cout << static_cast<long long>(value);
    } else {
        cout << fixed << setprecision(4) << value;
    }
}

int interpreter(ifstream &script, ifstream &input, Stack *stack) {
    bool first_output = true; 
    streampos loop_start = 0;
    Data loop_counter = 0;
    string command;

    while (script >> command) {
        Data value;
        if (parse_number(command, value)) {
            stack_push(stack, value);
        } else if (command == "peek") {
            if (stack_empty(stack)) {
                cerr << command << ": Stack is empty!";
                return 1;
            }
            if (!first_output) {
                cout << " ";
            }
            print(stack_get(stack));
            first_output = false;
        } else if (command == "add" || command == "sub" || command == "mul" || command == "div"){
            Data top, below;

            if (!pop_value(stack, top) || !pop_value(stack, below)) {
                cerr << command << ": Not enough elements on the stack!";
                return 1;
            }

            Data result = 0;
            if (command == "add") {
                result = top + below;
            } else if (command == "sub") {
                result = top - below;
            } else if (command == "mul") {
                result = top * below;
            } else {
                result = top / below;
            }
            stack_push(stack, result);
        } else if (command == "sq" || command == "sqrt") {
            Data x = 0;
            if (!pop_value(stack, x)) {
                cerr << command << ": Stack is empty!";
                return 1;
            }
            Data result = (command == "sq") ? (x * x) : sqrt(x);
            stack_push(stack, result);
        } else if (command == "get") {
            string word;
            if (!(input >> word)) {
                cerr << command << ": no more input data" << endl;
                return 1;
            }

            Data value = 0;
            if (!parse_number(word, value)) {
                cerr << command << ": is not a number";
                return 1;
            }
            stack_push(stack, value);
        } else if (command == "cond") {
            Data first = 0;
            if (!pop_value(stack, first) || stack_empty(stack)) {
                cerr << command << ": Stack is empty!";
                return 1;
            }
            
            Data second = stack_get(stack);
            if (round(first * 10000) == round(second * 10000)) {
                stack_pop(stack);
            } else if (!skip_after_cond_to_end(script)) {
                cerr << command << ": no matching end!";
                return 1;
            }
        } else if (command == "end") {
            // The end of the condition, nothing to do
        } else if (command == "setr") {
            if (!pop_value(stack, loop_counter)) {
                cerr << command << ": Stack is empty!";
                return 1;
            } 
            loop_start = script.tellg();
        } else if (command == "repeat") {
            if (loop_counter > 0) {
                loop_counter -= 1;
                script.seekg(loop_start);
            }   
        } else {
            cerr << command << ": unknown command!";
            return 1;
        }
    }
    cout << endl;
    return 0; 
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <script_file> <input_file>" << endl;
        return 2;
    }

    ifstream script_file(argv[1]);
    if (!script_file.is_open()) {
        cerr << "Error opening script file: " << argv[1] << endl;
        return 1;
    }

    ifstream input_file(argv[2]);
    if (!input_file.is_open()) {
        cerr << "Error opening input file: " << argv[2] << endl;
        return 1;
    }

    Stack *stack = stack_create();
    int interpreter_result = interpreter(script_file, input_file, stack);
    stack_delete(stack);

    return interpreter_result;
}