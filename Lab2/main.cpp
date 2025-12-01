#include "BeatnikInterpreter.h"
#include "stack.h"
#include "list.h"
#include <iostream>
#include <cstring>

int test_stack() {
    Stack<char> s;
    if (!s.empty()) return 1;
    s.push('A');
    if (s.get() != 'A') return 1;
    s.push('B');
    if (s.get() != 'B') return 1;
    s.pop();
    if (s.get() != 'A') return 1;
    s.pop();
    if (!s.empty()) return 1;
    return 0;
}

int test_list() {
    List<char> l;
    l.insert('C');
    l.insert('B');
    l.insert('A');

    auto i = l.first();
    if (!i || i->data() != 'A') return 1;
    i = i->next();
    if (!i || i->data() != 'B') return 1;
    i = i->next();
    if (!i || i->data() != 'C') return 1;
    if (i->next() != nullptr) return 1;

    l.erase_first();
    if (l.first()->data() != 'B') return 1;

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        if (std::strcmp(argv[1], "--test-stack") == 0) {
            return test_stack();
        }
        if (std::strcmp(argv[1], "--test-list") == 0) {
            return test_list();
        }
    }

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <script_file> <input_file>\n";
        std::cerr << "Or: " << argv[0] << " --test-stack\n";
        std::cerr << "Or: " << argv[0] << " --test-list\n";
        return 1;
    }

    BeatnikInterpreter interpreter(argv[2]);
    interpreter.run(argv[1]);
    return 0;
}