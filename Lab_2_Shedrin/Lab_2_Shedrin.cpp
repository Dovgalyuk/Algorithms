#include <iostream>
#include <string>
#include "../LibraryCPP/stack.h"
#include <list>
using namespace std;

//Преобразовать арифметическое выражение в ассемблерные опреации работы со стеком и регистрами.
//Используются команды PUSH(занести в стек), POP(извлечь из стека в регистр), ADD(сложить),
//SUB(вычесть), MUL(перемножить).Достаточно использовать два регистра A и B.
bool cintainis(list<int> f, int i) {
  
    for (int cont : f)
    {
        if (cont == i) { return false; }
    }
    return true;
}

void datareader(string in) {
    string nev = "";

    Stack* stack_number = stack_create();
    int stack_number_L = 0;
    for (size_t i = 0; i < in.length(); i++)
    {
      //  if (isdigit(in[i])) { stack_push(stack, in[i]-'0'); len++; } // отладка 
        if (in[i] == '(') {
            int stop = 0;
            for (size_t j = in.length(); j > 0; j--)
            {
                if (in[j] == ')') { stop = j; }
            }
            datareader(in.substr(i+1, stop - i));
            i = stop;
        }
        nev += in[i];
    }
   // cout << nev << "\n"; // отладка 
    // тяжело..
    list <int>number = {};
    Stack* stack_operand = stack_create();
    int stack_operand_L = 0;
    for (size_t i = 0; i < nev.length(); i++)
    {
        if (nev[i] == '*') { 
            if (isdigit(nev[i + 1]) && cintainis(number, i + 1)) { stack_push(stack_number, nev[i + 1] - '0'); stack_number_L++; number.push_back(i + 1); }
            if (isdigit(nev[i - 1]) && cintainis(number, i - 1)) { stack_push(stack_number, nev[i - 1] - '0'); stack_number_L++; number.push_back(i - 1); }
            //    ^знаю знаю это выглядит ужасно^ 
        }
    }
    for (size_t i = 0; i < nev.length(); i++)
    {
        if (nev[i] == '+' || nev[i] == '-') {
            if (isdigit(nev[i + 1]) && cintainis(number, i + 1)) { stack_push(stack_number, nev[i + 1] - '0'); stack_number_L++; number.push_back(i + 1); }
            if (isdigit(nev[i - 1]) && cintainis(number, i - 1)) { stack_push(stack_number, nev[i - 1] - '0'); stack_number_L++; number.push_back(i - 1); }
            //    ^это тоже выглядит ужасно^ 
        }
    }

    // тяжело.. пользыватся этим 
    for (size_t i = 0; i < nev.length(); i++)
    {
        if (nev[i] == '+' || nev[i] == '-') {
            stack_push(stack_operand, (int)nev[i]);
            stack_operand_L++;
        }
    }
    for (size_t i = 0; i < nev.length(); i++)
    {
        if (nev[i] == '*') {
            stack_push(stack_operand, (int)nev[i]);
            stack_operand_L++;
        }
    }
    // разбивать програму на функции ? а зачем ? (¬‿¬ )

    for (size_t i = 0; i < stack_number_L; i++)
    {
        cout <<"PUSH " << stack_get(stack_number) << "\n";
         stack_pop(stack_number);
    }
    for (size_t i = 0; i < stack_operand_L; i++)
    {
        int op =  stack_get(stack_operand);
        stack_pop(stack_operand);
        cout << "POP A " << "\n";
        cout << "POP B " << "\n";
        if (op == 42) cout << "MUL A, B" << "\n";
        else if (op == 43) cout << "ADD A, B" << "\n";
        else if (op == 45) cout << "SUB A, B" << "\n";
        else cout << "EROR" << "\n"; // как так то ? 
        cout << "PUSH A" << "\n";

    }
}

int main()
{
    string input;
    cin >> input;
    datareader(input);
}
