#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "../LibraryCPP/stack.h"

static inline int enc_int(int x) { return (x << 1); }
static inline int enc_ret(int pc) { return (pc << 1) | 1; }
static inline bool is_ret(int v) { return (v & 1) == 1; }
static inline int  dec_int(int v) { return (v >> 1); }
static inline int  dec_ret(int v) { return (v >> 1); }

struct Op { std::string name; int arg = 0; bool has_arg = false; };

static void print_error_and_exit(Stack* st) {
    std::cout << "error\n";
    stack_delete(st);
    std::exit(0);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto ltrim_inplace = [](std::string& s){
        size_t i = 0;
        while (i < s.size() && (unsigned char)s[i] <= 0x20) ++i;
        if (i) s.erase(0, i);
    };
    auto rtrim_inplace = [](std::string& s){
        while (!s.empty() && ((unsigned char)s.back() == '\r' || (unsigned char)s.back() == ' ' || (unsigned char)s.back() == '\t'))
            s.pop_back();
    };
    auto strip_bom_inplace = [](std::string& s){
        if (s.size() >= 3 &&
            (unsigned char)s[0] == 0xEF &&
            (unsigned char)s[1] == 0xBB &&
            (unsigned char)s[2] == 0xBF) {
            s.erase(0, 3);
        }
    };

    std::vector<Op> prog;
    std::string line;
    bool first_nonempty_seen = false;

    while (std::getline(std::cin, line)) {
        rtrim_inplace(line);
        ltrim_inplace(line);
        if (!first_nonempty_seen && !line.empty()) {
            strip_bom_inplace(line);
            ltrim_inplace(line);
            first_nonempty_seen = true;
        }
        if (line.empty()) continue;

        std::stringstream ss(line);
        Op op;
        ss >> op.name;
        if (ss >> op.arg) op.has_arg = true;
        prog.push_back(op);
    }

    int vars[4] = {0, 0, 0, 0};
    Stack* st = stack_create();

    int pc = 0;
    while (pc >= 0 && pc < (int)prog.size()) {
        const Op& ins = prog[pc];
        const std::string& nm = ins.name;

        if (nm == "bipush") {
            if (!ins.has_arg) print_error_and_exit(st);
            stack_push(st, enc_int(ins.arg));
            pc++;
        }
        else if (nm == "pop") {
            if (stack_empty(st)) print_error_and_exit(st);
            int v = stack_get(st);
            if (is_ret(v)) print_error_and_exit(st);
            stack_pop(st);
            pc++;
        }
        else if (nm == "iload_0" || nm == "iload_1" || nm == "iload_2" || nm == "iload_3") {
            int idx = nm.back() - '0';
            stack_push(st, enc_int(vars[idx]));
            pc++;
        }
        else if (nm == "istore_0" || nm == "istore_1" || nm == "istore_2" || nm == "istore_3") {
            int idx = nm.back() - '0';
            if (stack_empty(st)) print_error_and_exit(st);
            int v = stack_get(st);
            if (is_ret(v)) print_error_and_exit(st);
            vars[idx] = dec_int(v);
            stack_pop(st);
            pc++;
        }
        else if (nm == "swap") {
            if (stack_empty(st)) print_error_and_exit(st);
            int a = stack_get(st); stack_pop(st);
            if (stack_empty(st)) print_error_and_exit(st);
            int b = stack_get(st); stack_pop(st);
            stack_push(st, a);
            stack_push(st, b);
            pc++;
        }
        else if (nm == "iadd" || nm == "isub" || nm == "imul" ||
                 nm == "iand" || nm == "ior" || nm == "ixor") {
            if (stack_empty(st)) print_error_and_exit(st);
            int vb = stack_get(st); stack_pop(st);
            if (stack_empty(st)) print_error_and_exit(st);
            int va = stack_get(st); stack_pop(st);
            if (is_ret(va) || is_ret(vb)) print_error_and_exit(st);

            int A = dec_int(va), B = dec_int(vb), R = 0;
            if (nm == "iadd") R = A + B;
            else if (nm == "isub") R = A - B;
            else if (nm == "imul") R = A * B;
            else if (nm == "iand") R = A & B;
            else if (nm == "ior")  R = A | B;
            else if (nm == "ixor") R = A ^ B;

            stack_push(st, enc_int(R));
            pc++;
        }
        else if (nm == "invokestatic") {
            if (!ins.has_arg) print_error_and_exit(st);
            stack_push(st, enc_ret(pc + 1));
            pc = ins.arg;
        }
        else if (nm == "return") {
            if (stack_empty(st)) print_error_and_exit(st);
            int v = stack_get(st); stack_pop(st);
            if (!is_ret(v)) print_error_and_exit(st);
            pc = dec_ret(v);
        }
        else {
            print_error_and_exit(st);
        }
    }

    std::cout << "stack:\n";
    while (!stack_empty(st)) {
        int v = stack_get(st);
        stack_pop(st);
        if (!is_ret(v)) std::cout << dec_int(v) << "\n";
    }

    std::cout << "vars:\n";
    for (int i = 0; i < 4; ++i) std::cout << vars[i] << "\n";

    stack_delete(st);
    return 0;
}
