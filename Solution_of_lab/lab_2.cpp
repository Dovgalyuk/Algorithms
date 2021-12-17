#include <iostream>
#include <cctype>
#include "../LibraryCPPTemplate/stack.h"
#include "../LibraryCPPTemplate/vector.h"
#include <string>
using namespace std;


void check_symbol(Stack <string>& numbers, const  string& input);
bool is_number(const string& s);

int main() {
    Stack <string> polish_writeback;
    cout << "Input sample" << endl;
    string input;
    cin >> input;
    while (input != "=") {

        check_symbol(polish_writeback, input);
        cin >> input;
    }

    int result = stoi(polish_writeback.get());
    polish_writeback.pop();

    if (polish_writeback.empty()) {
        cout << result;
    }
    else {
        cout << "OVERFLOW" << endl;
        exit(-1);
    }
    return 0;
}


void check_symbol(Stack<string>& numbers, const  string& input) {

    if (numbers.empty()) {
        if (is_number(input)) {
            numbers.push(input);
            return;
        }
        else {
            cout << "FIRST_ELEMENT_NOT_DIGIT" << endl;
            exit(-1);
        }
    }


    if (is_number(input)) {
        numbers.push(input);
    }
    else {

        int second = stoi(numbers.get());
        numbers.pop();

        if (numbers.empty() || !is_number(numbers.get())) {
            cout << "UNDERFLOW" << endl;
            exit(-1);
        }

        int first = stoi(numbers.get());
        numbers.pop();

        int result;

        switch (input[0]) {
        case '-':
            result = first - second;
            break;
        case '+':
            result = first + second;
            break;
        case '/':
            if (second == 0) {
                cout << "ZERO";
                exit(-1);
            }
            result = first / second;
            break;
        case '*':
            result = first * second;
            break;
        default:
            cout << "String have unknown operation" << endl;
            exit(-1);
        }
        numbers.push(to_string(result));
    }
}




bool is_number(const string& s)
{
    return !s.empty() && find(s.begin(),
        s.end(), [](char c) { return !isdigit(c); }) == s.end();
}
