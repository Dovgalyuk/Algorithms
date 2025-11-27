#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include "stack.h"

using namespace std;

char tilde_value = '\0';
vector<string> variables(10);

bool is_numeric(const string& s) {
    if (s.empty()) {
        return false;
    }
    return all_of(s.begin(), s.end(), ::isdigit);
}

void processScript(Stack& stack, const string& script, const string& input) {
    size_t inputIndex = 0;
    bool in_if_block = false;
    bool if_condition_met = false;
    bool in_else_block = false;

    for (size_t i = 0; i < script.length(); ++i) {
        char cmd = script[i];

        if (in_if_block) {
            if (!if_condition_met && !in_else_block) {
                if (cmd == '|') {
                    in_else_block = true;
                    continue;
                }
                else if (cmd == '!') {
                    in_if_block = false;
                    in_else_block = false;
                    continue;
                }
                continue;
            }
            else if (in_else_block && if_condition_met) {
                if (cmd == '!') {
                    in_if_block = false;
                    in_else_block = false;
                    continue;
                }
                continue;
            }
        }

        switch (cmd) {
        case '+': {
            i++;
            string str;
            while (i < script.length()) {
                char c = script[i];
                if (c == '+' || c == '-' || c == '<' || c == '>' || c == '?' ||
                    c == '!' || c == ':' || c == '~' || c == '@' || c == '=' ||
                    c == '#' || c == '_' || c == '$' || c == '^' || c == '|') {
                    i--;
                    break;
                }
                str += c;
                i++;
            }
            for (char c : str) {
                stack.push(c);
            }
            break;
        }
        case '-': {
            if (!stack.empty()) {
                Stack temp;
                while (!stack.empty()) {
                    temp.push(stack.get());
                    stack.pop();
                }
                temp.pop();
                while (!temp.empty()) {
                    stack.push(temp.get());
                    temp.pop();
                }
            }
            break;
        }
        case '<': {
            Stack temp;
            while (!stack.empty()) {
                temp.push(stack.get());
                stack.pop();
            }
            while (!temp.empty()) {
                stack.push(temp.get());
                temp.pop();
            }
            break;
        }
        case '>': {
            i++;
            string output_text;
            while (i < script.length()) {
                char c = script[i];
                if (c == '+' || c == '-' || c == '<' || c == '>' || c == '?' ||
                    c == '!' || c == ':' || c == '~' || c == '@' || c == '=' ||
                    c == '#' || c == '_' || c == '$' || c == '^' || c == '|') {
                    i--;
                    break;
                }
                output_text += c;
                i++;
            }
            cout << output_text;
            break;
        }
        case '~': {
            if (i + 1 < script.length() && script[i + 1] == '\\') {
                tilde_value = '\0';
                i++;
            }
            else if (i + 1 < script.length() && script[i + 1] == '(') {
                i += 2;
                string num_str;
                while (i < script.length() && isdigit(script[i])) {
                    num_str += script[i];
                    i++;
                }
                i--;
                if (!num_str.empty() && is_numeric(num_str)) {
                    int var_num = stoi(num_str);
                    if (var_num >= 0 && var_num < 10) {
                        if (!variables[var_num].empty()) {
                            tilde_value = variables[var_num][0];
                        }
                        else {
                            tilde_value = '\0';
                        }
                    }
                }
            }
            else {
                if (!stack.empty()) {
                    Stack temp;
                    char bottom_value = '\0';
                    while (!stack.empty()) {
                        bottom_value = stack.get();
                        temp.push(stack.get());
                        stack.pop();
                    }
                    while (!temp.empty()) {
                        stack.push(temp.get());
                        temp.pop();
                    }
                    tilde_value = bottom_value;
                }
                else {
                    tilde_value = '\0';
                }
            }
            break;
        }
        case ':': {
            vector<char> elements;
            while (!stack.empty()) {
                elements.push_back(stack.get());
                stack.pop();
            }
            reverse(elements.begin(), elements.end());
            string combined;
            for (char c : elements) {
                combined += c;
            }
            for (char c : combined) {
                stack.push(c);
            }
            break;
        }
        case '?': {
            i++;
            bool is_not_equal = false;
            if (i < script.length() && script[i] == '!') {
                is_not_equal = true;
                i++;
            }
            string value_str;
            while (i < script.length() && script[i] != '!' && script[i] != '|') {
                value_str += script[i];
                i++;
            }
            i--;
            string tilde_str(1, tilde_value);
            if (is_not_equal) {
                if_condition_met = (tilde_str != value_str);
            }
            else {
                if_condition_met = (tilde_str == value_str);
            }
            in_if_block = true;
            in_else_block = false;
            break;
        }
        case '!': {
            i++;
            string index_str;
            while (i < script.length() && isdigit(script[i])) {
                index_str += script[i];
                i++;
            }
            i--;
            if (!index_str.empty() && is_numeric(index_str)) {
                int jump_index = stoi(index_str);
                if (jump_index >= 0 && jump_index < (int)script.length()) {
                    i = jump_index;
                }
            }
            else {
                in_if_block = false;
                in_else_block = false;
                if_condition_met = false;
            }
            break;
        }
        case '|': {
            if (in_if_block) {
                in_else_block = true;
            }
            break;
        }
        case '=': {
            if (i + 1 < script.length() && script[i + 1] == '(') {
                i += 2;
                string num_str;
                while (i < script.length() && isdigit(script[i])) {
                    num_str += script[i];
                    i++;
                }
                i--;
                if (!num_str.empty() && is_numeric(num_str)) {
                    int var_num = stoi(num_str);
                    if (var_num >= 0 && var_num < 10) {
                        variables[var_num] = string(1, tilde_value);
                    }
                }
            }
            else if (i + 1 < script.length() && script[i + 1] == ')') {
                i += 2;
                string num_str;
                while (i < script.length() && isdigit(script[i])) {
                    num_str += script[i];
                    i++;
                }
                i--;
                if (!num_str.empty() && is_numeric(num_str)) {
                    int var_num = stoi(num_str);
                    if (var_num >= 0 && var_num < 10) {
                        variables[var_num] = "";
                    }
                }
            }
            else {
                variables[0] = string(1, tilde_value);
            }
            break;
        }
        case '@': {
            i++;
            string num_str;
            while (i < script.length() && isdigit(script[i])) {
                num_str += script[i];
                i++;
            }
            i--;
            if (!num_str.empty() && is_numeric(num_str)) {
                int var_num = stoi(num_str);
                if (var_num >= 0 && var_num < 10 && !variables[var_num].empty()) {
                    for (char c : variables[var_num]) {
                        stack.push(c);
                    }
                }
            }
            break;
        }
        case '#': {
            return;
        }
        case '_': {
            string user_input;
            cout << "Input: ";
            cin >> user_input;
            for (char c : user_input) {
                stack.push(c);
            }
            break;
        }
        case '$': {
            i++;
            string num_str;
            while (i < script.length() && isdigit(script[i])) {
                num_str += script[i];
                i++;
            }
            i--;
            if (!num_str.empty() && is_numeric(num_str)) {
                int max_val = stoi(num_str);
                if (max_val > 0) {
                    int random_val = rand() % max_val + 1;
                    string random_str = to_string(random_val);
                    for (char c : random_str) {
                        stack.push(c);
                    }
                }
            }
            break;
        }
        case '^': {
            for (int j = 0; j < 50; j++) {
                cout << endl;
            }
            break;
        }
        default:
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <script_file> <input_file>" << endl;
        return 1;
    }

    srand(static_cast<unsigned int>(time(0)));

    string scriptFile = argv[1];
    string inputFile = argv[2];

    ifstream scriptStream(scriptFile);
    if (!scriptStream) {
        cerr << "Cannot open script file: " << scriptFile << endl;
        return 1;
    }
    string script;
    getline(scriptStream, script);
    scriptStream.close();

    ifstream inputStream(inputFile);
    if (!inputStream) {
        cerr << "Cannot open input file: " << inputFile << endl;
        return 1;
    }
    string input;
    getline(inputStream, input);
    inputStream.close();

    Stack stack;
    try {
        processScript(stack, script, input);

        Stack temp;
        while (!stack.empty()) {
            temp.push(stack.get());
            stack.pop();
        }
        while (!temp.empty()) {
            cout << (char)temp.get() << endl;
            temp.pop();
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}