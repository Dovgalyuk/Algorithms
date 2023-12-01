#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool isTag(const string& str) {
    return (str.size() > 2 && str[0] == '<' && str[1] != '/');
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    
    Stack* tagStack = stack_create();
    string tag;
    bool valid = true;

    while (getline(input, tag)) {
        if (isTag(tag)) {
            if (tag[1] != '/') {
                stack_push(tagStack, tag);
            } else {
                if (stack_empty(tagStack)) {
                    valid = false;
                    break;
                }
                string openTag = list_item_data(list_first(tagStack));
                openTag[1] = '/';
                if (openTag != tag) {
                    valid = false;
                    break;
                }
                stack_pop(tagStack);
            }
        }
    }

    if (!stack_empty(tagStack)) {
        valid = false;
    }

    if (valid) {
        output << "YES" << endl;
    } else {
        output << "NO" << endl;
    }

    stack_delete(tagStack);
    return 0;