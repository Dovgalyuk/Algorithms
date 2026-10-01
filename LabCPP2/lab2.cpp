#include "stack.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

class MinipigVM {
public:
    MinipigVM() : current(0), k(0), ip(0), printed_(false) {}

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
        dump_stack(stacks[0], out);
        dump_stack(stacks[1], out);
    }

private:
    Stack stacks[2];
    int current;
    int k;
    string program;
    size_t ip;
    istringstream input_stream;
    bool printed_;

    void switch_stack() {
        current ^= 1;
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
            if (!stacks[current].empty()) { k = stacks[current].get(); stacks[current].pop(); }
            ++ip; break;

        case 'v': case 'd':
            stacks[current].push(k);
            ++ip; break;

        case '/': case 's':
            stacks[current].swap();
            ++ip; break;

        case ';': case 'S':
            switch_stack();
            ++ip; break;

        case '1': case 'l':
            stacks[current].push(1);
            ++ip; break;

        case '-': case 'm': {
            if (stacks[current].empty()) { ++ip; break; }
            int a = stacks[current].get(); stacks[current].pop();
            if (stacks[current].empty()) { stacks[current].push(a); ++ip; break; }
            int b = stacks[current].get(); stacks[current].pop();
            stacks[current].push(b - a);
            ++ip; break;
        }

        case '[': case 'i': {
            int x = 0;
            if (!(input_stream >> x)) x = 0;
            stacks[current].push(x);
            ++ip; break;
        }

        case ']': case 'o':
            if (!stacks[current].empty()) {
                cout << stacks[current].get();
                stacks[current].pop();
                printed_ = true;
            }
            ++ip; break;

        case '{': case 'I': {
            char c = 0;
            if (!(input_stream >> c)) c = 0;
            stacks[current].push(static_cast<int>(c));
            ++ip; break;
        }

        case '}': case 'O':
            if (!stacks[current].empty()) {
                cout << static_cast<char>(stacks[current].get());
                stacks[current].pop();
                printed_ = true;
            }
            ++ip; break;

        case '%': case 'r':
            stacks[current].reverse();
            ++ip; break;

        case '*': case 'f':
            ++ip; break;

        case '>': case 'g': {
            if (stacks[current].empty()) { ++ip; break; }
            int n = stacks[current].get(); stacks[current].pop();
            goto_relative(n);
            break;
        }

        default:
            ++ip; break;
        }
    }

    static void dump_stack(const Stack& s, ostream& out) {
        Stack copy = s;
        copy.reverse();
        bool first = true;
        while (!copy.empty()) {
            if (!first) out << " ";
            out << copy.get();
            copy.pop();
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