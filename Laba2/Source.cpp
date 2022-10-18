#include <iostream>
#include <fstream>
#include <cctype>
#include "stack.h"
using namespace std;
int main() {
    //  10 9 - + (UNDERFLOW)
    //  1 2 + 3 (OVERFLOW)
    //  90 0 / (ZERO)
    Stack<int> number;
    bool ZERO = true;
    ifstream fin;
    fin.open("first.txt");
    char ch = ' ', last_ch = '.';
    if (fin.is_open()) {
        while (fin.get(ch)) {
            if (isdigit(ch)) {
                if (isdigit(last_ch)) {
                    int a = ch - '0', b = number.get();
                    number.pop();
                    number.push(10 * b + a);
                }
                else {
                    number.push(ch - '0');
                }
            }
            else if (ch != '\n'&&ch!=' ') {
                if (number.empty())
                    break;
                int a = number.get();
                number.pop();
                int b = 0;
                if (!number.empty()) {
                    b = number.get();
                    number.pop();
                    if (ch == '+') {
                        number.push(a + b);
                    }
                    if (ch == '-') {
                        number.push(a - b);
                    }
                    else if (ch == '/') {
                        if (a != 0) {
                            number.push(a + b);
                        }
                        else {
                            ZERO = false;
                        }
                    }
                }
                else {
                    number.push(a);
                    break;
                }
            }
            last_ch = ch;
        }
    }
    else {
        cout << "Open error!\n";
    }
    int j = 0;
    for (j = 0; !number.empty(); j++)
        number.pop();
    if (ZERO == true) {
        if (j > 1)  cout << "OVERFLOW" << endl;
        else if (j <= 2) cout << "UNDERFLOW" << endl;
    }
    else {
        cout << "ZERO" << std::endl;
    }
    fin.close();
    return 0;
}
