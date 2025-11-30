#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../LibraryCPP/list.h"
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

    for (size_t i = 0; i < input_values.size(); i++)
        stack_push(st, input_values[i]);


    bool first = true;

    for (const string& t : tokens)
    {
        if (t == "peek") {
            if (!stack_empty(st)) {
                int v = stack_get(st);
                if (!first) cout << " ";
                cout << v;
                first = false;
            }
            continue;
        }

        if (t == "setr") {
            if (!stack_empty(st)) {
                stack_pop(st);
            }
            continue;
        }

    }

    cout << endl;

    stack_delete(st);
    return 0;
}
