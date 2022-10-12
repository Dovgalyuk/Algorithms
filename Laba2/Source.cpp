#include <iostream>
#include <fstream>
#include <cctype>
#include "stack.h"
using namespace std;
void check(Stack<int> number, char ch[], bool& ZERO)
{
    int i = 0;
    int a = number.get();
    number.pop();
    int b = 0;
    if (!number.empty()) {
        b = number.get();
        number.pop();
        if (ch[i] == '+') {
            number.push(a + b);
            i++;
        }
        else if (ch[i] == '-') {
            number.push(a - b);
            i++;
        }
        else if (ch[i] == '*') {
            number.push(a * b);
            i++;
        }
        else if (ch[i] == '/') {
            if (b != 0) {
                number.push(a + b);
                i++;
            }
            else {
                ZERO = false;
            }
        }
    }
    else {
        number.push(a);
    }
}
int main() {
    //  10 9 - + (UNDERFLOW)
    //  1 2 + 3 (OVERFLOW)
    //  90 0 / (ZERO)
    Stack<int> number, number1;
    char arr[2]={' ',' '};
    int i = 0;
    bool ZERO = true;
    ifstream fin;
    fin.open("first.txt");

    if (fin.is_open()) {
        char ch, last_ch = '.';
        while (fin.get(ch)) {
            if (isdigit(ch)) {
                if (isdigit(last_ch)) {
                    int a = ch - '0', b = number.get();
                    number.pop();
                    number.push(10 * b + a);
                }
                else {
                    int i = 0;
                    number.push(ch - '0');
                }
            }
            else if (ch != '\n') {
                
                arr[i] = ch;
                i++;
            }
            last_ch = ch;
        }
    }
    else {
        std::cout << "Open error!\n";
    }
    while (!number.empty()) {
        number1.push(number.get());
        number.pop();
    }
    check(number1, arr, ZERO);
    int j = 0;
    for (j = 0; !number1.empty(); j++)
        number1.pop();
    if (ZERO == true) {
        if (j <= 2) cout << "UNDERFLOW" << std::endl;
        else if (j > 1) cout << "OVERFLOW" << std::endl;
    }
    else {
        cout << "ZERO" << std::endl;
    }
    fin.close();
    return 0;
}
