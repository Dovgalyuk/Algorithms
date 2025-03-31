#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include "stack.h"

using namespace std;

string to_lower(const string& str) {
    string lower_str = str;
    transform(lower_str.begin(), lower_str.end(), lower_str.begin(),
              [](unsigned char c) { return static_cast<char>(tolower(c)); });
    return lower_str;
}

bool is_opening_tag(const string& tag) {
    return tag[1] != '/';
}

string get_closing_tag(const string& opening_tag) {
    size_t start = opening_tag.find('<') + 1;
    size_t end = opening_tag.find_first_of(" >", start);
    string tag_name = opening_tag.substr(start, end - start);
    return "</" + to_lower(tag_name) + ">";
}

bool check_html_tags(ifstream& input) {
    Stack* stack = stack_create();
    string line;

    while (getline(input, line)) {
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (line.empty()) continue;

        if (is_opening_tag(line)) {
            stack_push(stack, line);
        } else {
            if (stack_empty(stack)) {
                stack_delete(stack);
                return false;
            }

            string top_tag = stack_get(stack);
            string expected_closing_tag = get_closing_tag(top_tag);

            
            if (to_lower(line) != expected_closing_tag) {
                stack_delete(stack);
                return false;
            }

            stack_pop(stack);
        }
    }

    bool result = stack_empty(stack);
    stack_delete(stack);
    return result;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc < 3) {
        cerr << "Ошибка: укажите путь к входному и выходному файлам." << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Ошибка: не удалось открыть входной файл " << argv[1] << endl;
        return 1;
    }

    ofstream outputFile(argv[2]);
    if (!outputFile) {
        cerr << "Ошибка: не удалось открыть выходной файл " << argv[2] << endl;
        inputFile.close();
        return 1;
    }

    if (check_html_tags(inputFile)) {
        outputFile << "YES" << endl;
    } else {
        outputFile << "NO" << endl;
    }

    inputFile.close();
    outputFile.close();
    return 0;
}