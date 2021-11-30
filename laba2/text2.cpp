#include <iostream>
#include <fstream>
#include "stack.h"

int main() {
    Stack<char> stk;

    std::ifstream fin;
    fin.open("../../laba2/txtfirst.txt");

    if (fin.is_open()){
       std::ofstream fout;
       fout.open("../../laba2/txtsecond.txt");
       char ch;
       while (fin.get(ch)){
           if (ch == '\n') {
               while (!stk.empty()) {
                   fout << stk.get();
                   stk.pop();
               }
               fout << '\n';
           }
           else {
               stk.push(ch);
           }
       }
       while (!stk.empty()) {
           fout << stk.get();
           stk.pop();
       }
       fout.close();
    }
    else {
        std:: cout << "Open error!\n";
    }
    fin.close();
}

