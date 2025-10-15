#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "stack.h"
using namespace std;

bool tags_match(const string& open_tag, const string& close_tag) {

    if (close_tag[0] != '<' || close_tag[1] != '/' || close_tag.back() != '>')
        return false;

    string open_name = open_tag.substr(1, open_tag.size() - 2);
    string close_name = close_tag.substr(2, close_tag.size() - 3);

    if (open_name.size() != close_name.size())
        return false;

    for (size_t i = 0; i < open_name.size(); ++i) {
        if (tolower(open_name[i]) != tolower(close_name[i]))
            return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " input.txt\n";
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "Cannot open input file\n";
        return 1;
    }

    Stack* stack = stack_create();
    bool valid = true;
    string line;

    while (getline(fin, line)) {
        if (line.empty()) continue;
        if (line.size() < 3 || line[0] != '<' || line.back() != '>') {
            valid = false;
            break;
        }
        if (line[1] != '/') {
            stack_push(stack, line);
        }
        else {
            if (stack_empty(stack)) {
                valid = false;
                break;
            }
            string open_tag = stack_get(stack);
            stack_pop(stack);
            if (!tags_match(open_tag, line)) {
                valid = false;
                break;
            }
        }
    }

    if (!stack_empty(stack))
        valid = false;

    stack_delete(stack);

    cout << (valid ? "YES\n" : "NO\n");

    return 0;
}