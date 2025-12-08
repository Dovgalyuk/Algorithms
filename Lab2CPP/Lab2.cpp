#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../LibraryCPP/stack.h"
using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 3) {
        cerr << "Usage: program script input" << endl;
        return 1;
    }

    vector<int> input_values;
    {
        ifstream in(argv[2]);
        int x;
        while (in >> x)
            input_values.push_back(x);
    }

    vector<string> tokens;
    {
        ifstream scr(argv[1]);
        string t;
        while (scr >> t)
            tokens.push_back(t);
    }

    Stack* st = stack_create();

    for (int v : input_values)
        stack_push(st, v);

    int left_reg = 0;
    int right_reg = 0;

    bool first_output = true;

    for (size_t ip = 0; ip < tokens.size(); ip++)
    {
        const string& t = tokens[ip];

        // число → push
        bool isNum = !t.empty() && (isdigit(t[0]) || t[0] == '-');
        if (isNum) {
            stack_push(st, stoi(t));
            continue;
        }

        if (t == "peek") {
            if (!stack_empty(st)) {
                int v = stack_get(st);
                if (!first_output) cout << " ";
                cout << v;
                first_output = false;
            }
            continue;
        }

        if (t == "pop") {
            if (!stack_empty(st)) stack_pop(st);
            continue;
        }

        if (t == "dup") {
            if (!stack_empty(st)) {
                int v = stack_get(st);
                stack_push(st, v);
            }
            continue;
        }

        if (t == "swap") {
            if (!stack_empty(st)) {
                int a = stack_get(st); stack_pop(st);
                if (!stack_empty(st)) {
                    int b = stack_get(st); stack_pop(st);
                    stack_push(st, a);
                    stack_push(st, b);
                } else {
                    stack_push(st, a);
                }
            }
            continue;
        }

        if (t == "setl") {
            if (!stack_empty(st)) {
                left_reg = stack_get(st);
                stack_pop(st);
            }
            continue;
        }

        if (t == "setr") {
            if (!stack_empty(st)) {
                right_reg = stack_get(st);
                stack_pop(st);
            }
            continue;
        }

        if (t == "getl") {
            stack_push(st, left_reg);
            continue;
        }

        if (t == "getr") {
            stack_push(st, right_reg);
            continue;
        }

        if (t == "add") {
            if (!stack_empty(st)) {
                int a = stack_get(st); stack_pop(st);
                if (!stack_empty(st)) {
                    int b = stack_get(st); stack_pop(st);
                    stack_push(st, b + a);
                } else stack_push(st, a);
            }
            continue;
        }

        if (t == "sub") {
            if (!stack_empty(st)) {
                int a = stack_get(st); stack_pop(st);
                if (!stack_empty(st)) {
                    int b = stack_get(st); stack_pop(st);
                    stack_push(st, b - a);
                } else stack_push(st, -a);
            }
            continue;
        }

        if (t == "mul") {
            if (!stack_empty(st)) {
                int a = stack_get(st); stack_pop(st);
                if (!stack_empty(st)) {
                    int b = stack_get(st); stack_pop(st);
                    stack_push(st, b * a);
                } else stack_push(st, 0);
            }
            continue;
        }

        if (t == "div") {
            if (!stack_empty(st)) {
                int a = stack_get(st); stack_pop(st);
                if (!stack_empty(st) && a != 0) {
                    int b = stack_get(st); stack_pop(st);
                    stack_push(st, b / a);
                } else stack_push(st, 0);
            }
            continue;
        }

        if (t == "mod") {
            if (!stack_empty(st)) {
                int a = stack_get(st); stack_pop(st);
                if (!stack_empty(st) && a != 0) {
                    int b = stack_get(st); stack_pop(st);
                    stack_push(st, b % a);
                } else stack_push(st, 0);
            }
            continue;
        }


        if (t == "loop") {
            size_t loop_start = ip + 1;

            int depth = 1;
            size_t j = loop_start;
            for (; j < tokens.size(); j++) {
                if (tokens[j] == "loop") depth++;
                if (tokens[j] == "pool") depth--;
                if (depth == 0) break;
            }

            size_t loop_end = j;

            while (!stack_empty(st) && stack_get(st) > 0) {
                size_t inner_ip = loop_start;
                while (inner_ip < loop_end) {
                    tokens.insert(tokens.begin() + inner_ip + 1, "");
                    inner_ip++;
                }
            }

            ip = loop_end;
            continue;
        }
    }

    cout << endl;

    stack_delete(st);
    return 0;
}
