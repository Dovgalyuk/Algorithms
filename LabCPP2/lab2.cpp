#include "stack.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

class MinipigVM {
public:
    MinipigVM() : current(&stack_a), k(0), ip(0), printed_(false) {}

    void load(const string& prog, const string& input) {
        program = prog;
        input_stream.str(input);
        input_stream.clear();
    }

    void run() {
        ip = 0;
        while (ip < program.size()) {
            exec(program[ip]);
        }
    }

    bool printed() const { return printed_; }

    void dump(ostream& out = cout) const {
        dump_stack(stack_a, out);
        dump_stack(stack_b, out);
    }

private:
    Stack stack_a;
    Stack stack_b;
    Stack* current;
    int k;
    string program;
    size_t ip;
    istringstream input_stream;
    bool printed_;

    void switch_stack() {
        current = (current == &stack_a) ? &stack_b : &stack_a;
    }

    void goto_relative(int n) {
        ++ip;
        if (n == 0) return;

        if (n > 0) {
            int count = 0;
            while (ip < program.size() && count < n) {
                if (program[ip] == '*') ++count;
                ++ip;
            }
            if (count < n) {
                throw runtime_error("невалидный флаг: не найдено " +
                    to_string(n) + " звёздочек вперёд");
            }
        }
        else {
            int need = -n;
            int count = 0;
            while (ip > 0 && count < need) {
                --ip;
                if (program[ip] == '*') ++count;
            }
            if (count < need) {
                throw runtime_error("невалидный флаг: не найдено " +
                    to_string(need) + " звёздочек назад");
            }
            if (ip > 0 && program[ip] == '*') ++ip;
        }
    }

    void exec(char op) {
        switch (op) {

        case '^': case 'u':
            if (!current->empty()) { k = current->get(); current->pop(); }
            ++ip; break;

        case 'v': case 'd':
            current->push(k);
            ++ip; break;

        case '/': case 's':
            current->swap();
            ++ip; break;

        case ';': case 'S':
            switch_stack();
            ++ip; break;

        case '1': case 'l':
            current->push(1);
            ++ip; break;

        case '-': case 'm': {
            if (current->empty()) { ++ip; break; }
            int a = current->get(); current->pop();
            if (current->empty()) { current->push(a); ++ip; break; }
            int b = current->get(); current->pop();
            current->push(b - a);
            ++ip; break;
        }

        case '[': case 'i': {
            int x = 0;
            if (!(input_stream >> x)) x = 0;
            current->push(x);
            ++ip; break;
        }

        case ']': case 'o':
            if (!current->empty()) {
                cout << current->get();
                current->pop();
                printed_ = true;
            }
            ++ip; break;

        case '{': case 'I': {
            char c = 0;
            if (!(input_stream >> c)) c = 0;
            current->push(static_cast<int>(c));
            ++ip; break;
        }

        case '}': case 'O':
            if (!current->empty()) {
                cout << static_cast<char>(current->get());
                current->pop();
                printed_ = true;
            }
            ++ip; break;

        case '%': case 'r':
            current->reverse();
            ++ip; break;

        case '*': case 'f':
            ++ip; break;

        case '>': case 'g': {
            if (current->empty()) { ++ip; break; }
            int n = current->get(); current->pop();
            goto_relative(n);
            break;
        }

        default:
            ++ip; break;
        }
    }

    static void dump_stack(const Stack& s, ostream& out) {
        Stack copy = s;
        Stack rev;
        while (!copy.empty()) { rev.push(copy.get()); copy.pop(); }
        bool first = true;
        while (!rev.empty()) {
            if (!first) out << " ";
            out << rev.get();
            rev.pop();
            first = false;
        }
        out << "\n";
    }
};

static string read_file(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("не удалось открыть файл " + filename);
    }
    return string((istreambuf_iterator<char>(file)),
        istreambuf_iterator<char>());
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Использование: " << argv[0] << " <скрипт> [<входные данные>]\n";
        return 1;
    }

    try {
        string program = read_file(argv[1]);
        string input;
        if (argc >= 3) {
            input = read_file(argv[2]);
        }

        if (program.empty()) {
            cerr << "Ошибка: скрипт пуст\n";
            return 1;
        }

        MinipigVM vm;
        vm.load(program, input);
        vm.run();

        if (vm.printed()) cout << "\n";
        vm.dump(cout);

    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }
    return 0;
}