#include "iostream"
#include "fstream"
#include "string"
#include "cstdlib"
#include "stack.h"
using namespace std;

typedef Stack<int> MyStack;

int main(){
    MyStack test;
    int A[1] = {0}, B[1] = {0}, C[1] = {0}, D[1] = {0};
    string _string;
    ifstream file("C:\\Users\\vasya\\OneDrive\\Desktop\\file.txt");
    if(file.is_open()) {
        while (!file.eof()) {
            getline(file, _string);
            if (!_string.find("PUSH ")) {
                if (_string[5] == 'A') {
                    test.push(A[0]);
                } else if (_string[5] == 'B') {
                    test.push(B[0]);
                } else if (_string[5] == 'C') {
                    test.push(C[0]);
                } else if (_string[5] == 'D') {
                    test.push(D[0]);
                }else{
                    string str = _string.substr(5);
                    test.push(atoi(str.c_str()));
                }

            }
            if(test.empty()) {
                cout << "Stack is empty" << endl;
                break;
            }
            else if (!_string.find("POP ")) {
                if (_string[4] == 'A') {
                    A[0] = test.get();
                    test.pop();
                } else if (_string[4] == 'B') {
                    B[0] = test.get();
                    test.pop();
                } else if (_string[4] == 'C') {
                    C[0] = test.get();
                    test.pop();
                } else if (_string[4] == 'D') {
                    D[0] = test.get();
                    test.pop();
                } else {
                    cout << "Error" << endl << endl;
                    file.eof();
                }
            }
        }
    }
    else
        cout << "File is not open" << endl << endl;
        cout << "A = " << *A << endl << "B = " << *B << endl << "C = " << *C << endl << "D = " << *D << endl;


    return 0;
}