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
                _string = _string[5];
                if (!_string.find('A')) {
                    test.push(A[0]);
                } else if (!_string.find('B')) {
                    test.push(B[0]);
                } else if (!_string.find('C')) {
                    test.push(C[0]);
                } else if (!_string.find('D')) {
                    test.push(D[0]);
                } else
                    test.push(atoi(_string.c_str()));
            }
            if(test.empty()) {
                cout << "Stack is empty" << endl;
                break;
            }
            else if (!_string.find("POP ")) {
                _string = _string[4];
                if (!_string.find('A')) {
                    A[0] = test.get();
                    test.pop();
                } else if (!_string.find('B')) {
                    B[0] = test.get();
                    test.pop();
                } else if (!_string.find('C')) {
                    C[0] = test.get();
                    test.pop();
                } else if (!_string.find('D')) {
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