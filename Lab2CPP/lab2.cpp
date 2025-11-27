#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <string_view>
#include "stack.h"

using namespace std;

void lower_case(string& s)  {
    for (char& c : s) {
        if (!isspace(static_cast<unsigned char>(c))) {
            c = tolower(static_cast<unsigned char> (c));
        }
    }
}

int main(int argc, char **argv) {
    ifstream input(argv[1]);

    string line;
    Stack<string> stackTag;

    try {
        while (getline(input, line)) {
            lower_case(line);

            for (size_t i = 0; i < line.size(); i++) {
                if (line[i] == '<') {
                    i++;

                    bool isClosing = false;
                    if (line[i] == '/') {
                        isClosing = true;
                        i++;
                    }

                    size_t start = i;
                    size_t end = line.find('>', start);
                    if (end == string::npos) {
                        cout << "NO" << endl;
                        return 1;
                    }

                    string_view tagName = string_view(line).substr(start, end - start);

                    if (isClosing) {
                        if (stackTag.empty() || stackTag.get() != tagName) {
                            cout << "NO" << endl;
                            return 1;
                        }
                        stackTag.pop();
                    } else {
                        stackTag.push(string(tagName));
                    }

                    i = end;
                }
            }
        }
        if (stackTag.empty()) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        input.close();
        return 1;
    }

    input.close();
}