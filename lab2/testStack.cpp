#include <iostream>
#include "stack.h"
#include <fstream>
#include <string>


typedef Stack<int> steck;

int main() {
    steck registr;
    int A = 0,
        B = 0,
        C = 0,
        D = 0;

    std::string stroka;
    std::ifstream in("E:\\text.txt");

    if(in.is_open()) {
        while (!in.eof()) {
            std::getline(in, stroka); // Получаем строку
            if (!stroka.find("PUSH ")) { // Если находит команду PUSH
                if (stroka[5] == 'A') // Проверяет какой символ был введен после команды PUSH
                    registr.push(A);
                else if (stroka[5] == 'B')
                    registr.push(B);
                else if (stroka[5] == 'C')
                    registr.push(C);
                else if (stroka[5] == 'D')
                    registr.push(D);
                else
                {
                    std::string str = stroka.substr(5); // Получаем число
                    registr.push(atoi(str.c_str())); // Добавляет в вершину
                }
            }
            if(registr.empty()) {
                std::cout << "Stack is empty";
                break;
            }
            if (!stroka.find("POP")) {  //Если находится команда POP
                if (stroka[4] == 'A') { // Проверяет какой символ был введен после команды POP
                    A = registr.get();
                    registr.pop();
                } else if (stroka[4] == 'B') {
                    B = registr.get();
                    registr.pop();
                } else if (stroka[4] == 'C') {
                    C = registr.get();
                    registr.pop();
                } else if (stroka[4] == 'D') {
                    D = registr.get();
                    registr.pop();
                } else {
                    std::cout << "Error" << std::endl << std::endl;
                    in.eof();
                }
            }
        }
    }
    std::cout << "A = " << A << std::endl;
    std::cout << "B = " << B << std::endl;
    std::cout << "C = " << C << std::endl;
    std::cout << "D = " << D << std::endl;

    return 0;
}