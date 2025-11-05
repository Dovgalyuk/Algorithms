#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include "stack.h"

using namespace std;

struct Token {
    enum Kind { NUM, WORD } kind;
    int value;
    string text;
};

static vector<Token> tokenize(const string &src) {
    istringstream iss(src);
    vector<Token> tokens;
    string w;
    while (iss >> w) {
        try {
            int v = stoi(w);
            tokens.push_back({Token::NUM, v, w});
        } catch (...) {
            tokens.push_back({Token::WORD, 0, w});
        }
    }
    return tokens;
}

int main(int argc, char **argv) {
    if (argc != 3) return 1;

    ifstream script(argv[1]);
    ifstream input(argv[2]);
    if (!script || !input) return 1;

    stringstream buf;
    buf << script.rdbuf();
    auto tokens = tokenize(buf.str());

    vector<int> inputs;
    for (int v; input >> v; ) inputs.push_back(v);
    size_t in_pos = 0;

    Stack *st = stack_create();
    ostringstream out;
    bool first_out = true;

    int reg = 0;
    vector<pair<int, ptrdiff_t>> loops;

    auto skip_to_end = [&](size_t &i) {
        int depth = 1;
        for (++i; i < tokens.size(); ++i) {
            if (tokens[i].kind == Token::WORD) {
                if (tokens[i].text == "cond") depth++;
                else if (tokens[i].text == "end" && --depth == 0) break;
            }
        }
    };

    for (size_t i = 0; i < tokens.size(); ++i) {
        auto &t = tokens[i];

        if (t.kind == Token::NUM) {
            stack_push(st, t.value);
            continue;
        }

        const auto &op = t.text;

        if (op == "add" || op == "sub" || op == "mul" || op == "div" || op == "mod") {
            if (stack_empty(st)) { stack_delete(st); return 2; }
            int b = stack_get(st); stack_pop(st);
            if (stack_empty(st)) { stack_delete(st); return 2; }
            int a = stack_get(st); stack_pop(st);

            if (op == "add") stack_push(st, a + b);
            else if (op == "sub") stack_push(st, a - b);
            else if (op == "mul") stack_push(st, a * b);
            else if (op == "div") {
                if (b == 0) { stack_delete(st); return 3; }
                stack_push(st, a / b);
            } else if (op == "mod") {
                if (b == 0) { stack_delete(st); return 3; }
                stack_push(st, a % b);
            }
        }
        else if (op == "sqrt" || op == "sq") {
            if (stack_empty(st)) { stack_delete(st); return 2; }
            int a = stack_get(st); stack_pop(st);
            if (op == "sqrt") {
                if (a < 0) { stack_delete(st); return 4; }
                stack_push(st, (int)floor(sqrt((double)a)));
            } else stack_push(st, a * a);
        }
        else if (op == "get") {
            if (in_pos >= inputs.size()) { stack_delete(st); return 5; }
            stack_push(st, inputs[in_pos++]);
        }
        else if (op == "peek") {
            if (stack_empty(st)) { stack_delete(st); return 2; }
            int v = stack_get(st);
            if (!first_out) out << ' ';
            first_out = false;
            out << v;
        }
        else if (op == "cond") {
            if (stack_empty(st)) { skip_to_end(i); continue; }
            int a = stack_get(st); stack_pop(st);
            if (stack_empty(st)) { skip_to_end(i); continue; }
            int b = stack_get(st); stack_pop(st);

            if (a == b) {
                stack_push(st, a);
            } else {
                stack_push(st, a);
                skip_to_end(i);
            }
        }
        else if (op == "setr") {
            if (stack_empty(st)) { stack_delete(st); return 2; }
            reg = stack_get(st);
            stack_pop(st);
            loops.push_back({reg, (ptrdiff_t)i + 1});
        }
        else if (op == "repeat") {
            if (!loops.empty()) {
                auto &top = loops.back();
                if (--top.first > 0)
                    i = (size_t)top.second - 1;
                else
                    loops.pop_back();
            }
        }
        else if (op == "end") {
        }
        else {
            stack_delete(st);
            return 6;
        }
    }

    cout << out.str() << "\n";
    stack_delete(st);
    return 0;
}
