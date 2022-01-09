#include <iostream>
#include <fstream>
#include "stack.h"

int main() {
    Stack<char> stk;

    std::ifstream fin; // на чтение
    fin.open("../../laba2/txtfirst.txt");

    if (fin.is_open()){
       std::ofstream fout; // запись
       fout.open("../../laba2/txtsecond.txt");
       char ch;
       while (fin.get(ch)){
           if (ch == '\n') {
               while (!stk.empty()) { // пока стек не пуст
                   fout << stk.get(); // данные посл эл
                   stk.pop(); // del
               }
               fout << '\n';
           }
           else {
               stk.push(ch); // запихнуть в стек
           }
       }
       while (!stk.empty()) { // вывод стека
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

