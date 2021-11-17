#include <iostream>
#include "stack.h"
#include <stdlib.h>


void underflow(Stack*& stack1) {
    stack_pop(stack1);
    if (stack_empty(stack1)) {
        std::cout << "UNDERFLOW";
        exit(1);
    }
}

void popPush(Stack*& stack1, int temptop) {
    stack_pop(stack1);
    stack_push(stack1, temptop);
}

int main()
{

    std::string polishMath;
    std::string number;


    Stack* stack1 = stack_create();
    int temptop = 0;



    std::cout << "Write down your math expression using after each operator " << "Enter. If something wasn't printed push your key again. " << std::endl;
    std::cout << "After you've finished write down " << "! and push Enter and you will get the answer" << std::endl;

    while (true) {

        std::cin >> polishMath;
        if (polishMath == "!") {
            break;
        }
        switch (polishMath[0]) {
        case '+':
            underflow(stack1);

            temptop += stack_get(stack1);
            popPush(stack1, temptop);
            break;
        case '-':
            underflow(stack1);

            temptop = stack_get(stack1) - temptop;
            popPush(stack1, temptop);
            break;
        case '/':
            underflow(stack1);

            if (temptop == 0) {
                std::cout << "ZERO";
                exit(1);
            }
            temptop = stack_get(stack1) / temptop;
            popPush(stack1, temptop);
            break;
        case '*':
            underflow(stack1);

            temptop *= stack_get(stack1);
            popPush(stack1, temptop);
            break;
        default:
            stack_push(stack1, std::atoi(polishMath.c_str()));
            temptop = stack_get(stack1);
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
