#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "stack.h"

using namespace std;

void summa(Stack* stack){
    if((stack_size(stack) < 2)){
        cout << "error sum\n" << endl;
        return;
    }
    int one, two, result;
    two = stack_take(stack);
    one = stack_take(stack);
    result = one + two;
    stack_push(stack, result);
}

void minuss(Stack* stack){
    if((stack_size(stack) < 2)){
        cout << "error minus\n" << endl;
        return;
    }
    int one, two, result;
    two = stack_take(stack);
    one = stack_take(stack);
    result = one - two;
    stack_push(stack, result);
}
// *
void increase(Stack* stack){
    if((stack_size(stack) < 2)){
        cout << "error increase\n" << endl;
        return;
    }
    int one, two, result;
    two = stack_take(stack);
    one = stack_take(stack);
    result = one * two;
    stack_push(stack, result);
}
// /
void division(Stack* stack){
    if((stack_size(stack) < 2)){
        cout << "error division\n" << endl;
        return;
    }
    int one, two, result;
    two = stack_take(stack);
    one = stack_take(stack);
    if(two == 0){
        cout << "division by zero error\n";
        return;
    }
    else {
        result = one / two;
        stack_push(stack, result);
    }

}
// %
void remainder(Stack* stack){
    if((stack_size(stack) < 2)){
        cout << "error remainder\n" << endl;
        return;
    }
    int one, two, result;
    two = stack_take(stack);
    one = stack_take(stack);
    result = one % two;
    stack_push(stack, result);
}

void dup(Stack* stack){
    if(stack_empty(stack)){
        cout << "stack empty\n" << endl;
        return;
    }
    int one;
    one = stack_get(stack);
    stack_push(stack, one);
}

void drop(Stack* stack){
    if(stack_empty(stack)){
        cout << "stack empty\n" << endl;
        return;
    }
    stack_pop(stack);
}
// поменять местами
void swap_stack(Stack* stack){
    if((stack_size(stack) < 2)){
        cout << "error swap\n" << endl;
        return;
    }
    int one, two;
    two = stack_take(stack);
    one = stack_take(stack);
    stack_push(stack, two);
    stack_push(stack, one);
}
// копирование второго
void over(Stack* stack){
    if((stack_size(stack) < 2)){
        cout << "error over\n" << endl;
        return;
    }
    int one, two;
    two = stack_take(stack);
    one = stack_get(stack);
    stack_push(stack, one);
    stack_push(stack, two);
}
// сдвиг
void rot(Stack* stack) {
    if (stack_size(stack) < 3) {
        cout << "error rot\n";
        return;
    }

    int a3 = stack_take(stack); 
    int a2 = stack_take(stack); 
    int a1 = stack_take(stack); 

    stack_push(stack, a2);
    stack_push(stack, a3);
    stack_push(stack, a1);
}

void write(Stack* stack){
    if(stack_empty(stack)){
        cout << "stack empty\n";
        return;
    }
    cout << stack_take(stack) << '\n';
}

void determinant_operator(Stack *stack, string command){
    if(command == "+") summa(stack);
    else if(command == "-") minuss(stack);
    else if(command == "*") increase(stack);
    else if(command == "/") division(stack);
    else if(command == "%") remainder(stack);

    else if(command[0] >= '0' && command[0] <= '9' && command.size() == 1){
        stack_push(stack, stoi(command));
    }
    else if(command == "dup") dup(stack);
    else if(command == "drop") drop(stack);
    else if(command == "swap") swap_stack(stack);
    else if(command == "over") over(stack);
    else if(command == "rot") rot(stack);
    else if(command == ".") write(stack);
    else cout << "ignore bad massage\n";
}

string read_file(istream &input){
    string a;
    getline(input, a);
    return a;
}

int main(int argc, char **argv){
    string stroka, command;
    Stack* stack = stack_create();
    stringstream ss;
    if (argc > 1){

        ifstream FILE(argv[1]);
        if (!FILE.is_open()){
            return -1;
        }
        
        stroka = read_file(FILE);
        FILE.close();
        ss << stroka;
        while(ss >> command){
            determinant_operator(stack, command);
        }   

    }

    else{
        getline(cin, stroka);
        ss << stroka;
        while(ss >> command){
            determinant_operator(stack, command);
        }        
    }
    stack_delete(stack);
    return 0;
}

