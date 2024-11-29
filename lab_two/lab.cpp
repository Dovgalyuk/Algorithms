#include <iostream>
#include <fstream>
#include <vector>
#include "stack.h"

using namespace std;

bool test (vector<char> &s, vector<char> &w);

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file_path>" << endl;
        return 1;
    }

    ifstream input(argv[1]);

    if (!input) {
        cout << "Opening error" <<  endl;
        return 1;
    }

    char c;
    vector<char> s;
    vector<char> w;

    while (input.get(c)) {
        if (c == '*') { 
            break;
        }
        s.push_back(c);
    }

    while (input.get(c)) w.push_back(c);

    if (test(s, w)) cout << "YES";
    else cout << "NO";

    input.close();
}

bool test (vector<char> &s, vector<char> &w) {
    if (s.size() != w.size()) {
        return false;
    }

    Stack* stack = stack_create();

    for (char c : s) {
        stack_push(stack, c);
    }

    for (char c : w) {
        if (stack_empty(stack) || stack_get(stack) != c) {
            stack_delete(stack);
            return false;
        }
        stack_pop(stack);
    }

    stack_delete(stack);

    return true;
}