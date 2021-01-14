#include <iostream>
#include "List.h"
#include "Stack.h"
#include <vector>


void test_list();

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}

void do_operation(Stack<char>& operations, Stack<double>& numbers){
    if (numbers.size() < 2){
        std::cerr << "UNDERFLOW" << std::endl;
        exit(1);
    }
    switch (operations.top()) {
        case '+': {
            double first = numbers.top();
            numbers.pop();
            double second = numbers.top();
            numbers.pop();
            numbers.push(first + second);
            break;
        }
        case '-': {
            double first = numbers.top();
            numbers.pop();
            double second = numbers.top();
            numbers.pop();
            numbers.push(first - second);
            break;
        }
        case '*': {
            double first = numbers.top();
            numbers.pop();
            double second = numbers.top();
            numbers.pop();
            numbers.push(first * second);
            break;
        }
        case '/': {
            double first = numbers.top();
            numbers.pop();
            double second = numbers.top();
            numbers.pop();
            if (second == 0){
                std::cerr << "ZERO" << std::endl;
                exit(1);
            }
            numbers.push(first / second);
            break;
        }
        default: {
            std::cout << "unknown operation" << std::endl;
            exit(1);
        }
    }
    operations.pop();
}

void lab2(){
    Stack<char> operations;
    Stack<double> numbers;

    std::string input;
    getline(std::cin, input);

    std::vector<std::string> buffer;

    split(input, buffer, ' ');
    for(const auto& str : buffer){
        if (str.length() == 1 && (str[0] == '-' || str[0] == '+' || str[0] == '*' || str[0] == '/')){
            operations.push(str[0]);
            do_operation(operations, numbers);
        } else {
            try{
                double value = std::stod(str);
                numbers.push(value);
            }
            catch(std::exception& e){
                std::cerr << e.what() << std::endl;
            }
        }
    }

   /*while (operations.size() > 0) {
        do_operation(operations, numbers);
    }*/

    if (numbers.size() > 1) {
        std::cerr << "OVERFLOW" << std::endl;
        exit(1);
    }
    std::cout << "result = " << numbers.top() << std::endl;
    numbers.pop();

}


int main() {
    lab2();
    //test_list();
}

void test_list() {
    List<int> list;

    list.insert(1);
    list.insert(2);
    list.insert(3);

    if (list.first() != 3)
        std::cout << "list_insert error\n";

    list.insert_after(list.first(), 4);

    if (list.next(list.first()) != 4)
        std::cout << "list_insert_after error\n";

    list.drop_first();// == list.erase(list.first());

    if (list.first() != 4)
        std::cout << "list_erase error\n";

    std::cout << "List: ";
    list.print();

}



