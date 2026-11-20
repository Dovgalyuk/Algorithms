#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <stdexcept>
#include "stack.h"

using namespace std;

struct Instruction {
    string command;
    string arg;
};

struct Value {
    int number;
    bool is_address;
};

typedef vector<Value> StackValues;

class VMStack {
    Stack data;
    Stack flags;

public:
    bool empty() const {
        return data.empty();
    }

    void push(int n, bool address = false) {
        data.push(n);
        flags.push(address ? 1 : 0);
    }

    Value top() const {
        if (empty()) throw runtime_error("Stack is empty");
        return { data.get(), flags.get() != 0 };
    }

    int pop_number() {
        Value v = top();
        if (v.is_address) throw runtime_error("Expected number");

        data.pop();
        flags.pop();
        return v.number;
    }

    int pop_address() {
        Value v = top();
        if (!v.is_address) throw runtime_error("Expected return address");

        data.pop();
        flags.pop();
        return v.number;
    }

    void swap_top() {
        Stack flags_copy = flags;

        if (flags_copy.empty()) throw runtime_error("Invalid swap");
        if (flags_copy.get()) throw runtime_error("Invalid swap");
        flags_copy.pop();

        if (flags_copy.empty() || flags_copy.get())
            throw runtime_error("Invalid swap");

        int a = data.get(); data.pop();
        int b = data.get(); data.pop();
        data.push(a);
        data.push(b);
    }

    StackValues values() const {
        StackValues result;
        Stack data_copy = data;
        Stack flags_copy = flags;

        while (!data_copy.empty()) {
            result.push_back({ data_copy.get(), flags_copy.get() != 0 });
            data_copy.pop();
            flags_copy.pop();
        }

        return result;
    }
};

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) throw runtime_error("Usage: VM <input_file>");

        ifstream file(argv[1]);
        if (!file) throw runtime_error("Cannot open input file");

        vector<Instruction> program;
        string line;

        while (getline(file, line)) {
            istringstream in(line);
            Instruction ins;

            if (!(in >> ins.command)) continue;
            in >> ins.arg;

            program.push_back(ins);
        }

        VMStack stack;
        array<int, 4> vars = { 0, 0, 0, 0 };
        vector<int> calls;
        size_t pc = 0;

        while (pc < program.size()) {
            Instruction ins = program[pc++];
            string c = ins.command;

            if (c == "bipush") {
                if (ins.arg.empty())
                    throw runtime_error("bipush needs one number");
                stack.push(stoi(ins.arg));
            }
            else if (c == "pop") stack.pop_number();
            else if (c == "swap") stack.swap_top();
            else if (c == "iadd" || c == "isub" || c == "imul" ||
                c == "iand" || c == "ior" || c == "ixor") {
                int b = stack.pop_number(), a = stack.pop_number(), r = 0;

                if (c == "iadd") r = a + b;
                if (c == "isub") r = a - b;
                if (c == "imul") r = a * b;
                if (c == "iand") r = a & b;
                if (c == "ior")  r = a | b;
                if (c == "ixor") r = a ^ b;

                stack.push(r);
            }
            else if (c.size() == 7 && c.substr(0, 6) == "iload_")
                stack.push(vars[c[6] - '0']);
            else if (c.size() == 8 && c.substr(0, 7) == "istore_")
                vars[c[7] - '0'] = stack.pop_number();
            else if (c == "invokestatic") {
                int target = stoi(ins.arg);
                if (target < 0 || target >= (int)program.size())
                    throw runtime_error("Invalid function address");

                stack.push((int)pc, true);
                calls.push_back(target);
                pc = target;
            }
            else if (c == "return") {
                int address = stack.pop_address();
                if (address < 0 || address >(int)program.size())
                    throw runtime_error("Invalid return address");
                pc = address;
            }
            else throw runtime_error("Unknown instruction: " + c);
        }

        cout << "stack:\n";
        for (Value v : stack.values()) {
            if (v.is_address) cout << "return address: ";
            cout << v.number << '\n';
        }

        cout << "vars:\n";
        for (int v : vars) cout << v << '\n';

        cout << "call sequence:\n";
        for (int v : calls) cout << v << '\n';
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}