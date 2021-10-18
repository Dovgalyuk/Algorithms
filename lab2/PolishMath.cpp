#include <iostream>
#include <conio.h>
#include "stack.h"
#include <stdlib.h>


int main()
{
    const int esc = 27;

    std::string polishMath;
    std::string number;
    

    Stack* stack1 = stack_create();
    int temptop = 0;

    
    char ch = 0;

    std::cout << "Write down your math expression using after each operator " << "Enter. If something wasn't printed push your key again. " << std::endl;
    std::cout << "After you've finished push " << "Esc and you'll get the answer" << std::endl;

    while (true) {
        
        std::cin >> polishMath;
        
        if ((polishMath != "+") and (polishMath != "-") and (polishMath != "/") and (polishMath != "*")) {
            stack_push(stack1, std::atoi(polishMath.c_str()));
        }
        else {
            number += polishMath;
        }
        if (number != "") {
            temptop = stack_get(stack1);
            stack_pop(stack1);
            if (stack_empty(stack1)) {
                std::cout << "UNDERFLOW";
                exit(1);
            }
        }
        switch (number[0]) {
            case '+':
                temptop += stack_get(stack1);
                break;
            case '-':
                temptop = stack_get(stack1) - temptop;
                break;
            case '/':
                if (temptop == 0) {
                    std::cout << "ZERO";
                    exit(1);
                }
                temptop = stack_get(stack1) / temptop;
                break;
            case '*':
                temptop *= stack_get(stack1);
                break;
        }
        if (number != ""){
            stack_pop(stack1);
            stack_push(stack1, temptop);
            temptop = 0;
        }
        number = "";
        ch = _getch();
        if (ch == esc) {
            break;
        }
    }
    temptop = stack_get(stack1);
    stack_pop(stack1);
    if (stack_empty(stack1)) {
        std::cout << "Answer: " << temptop << std::endl;
    }
    else {
        std::cout << "OVERFLOW";
        exit(1);
    }
    

    stack_delete(stack1);
}

//Sword & Sworcery's