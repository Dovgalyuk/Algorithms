#include <iostream>
#include "queue.h"

/*
Задано начальное вещество и список химических реакций,
в которых оно превращается в другое вещество.
Написать программу, использующую поиск в ширину,
и выводящую список веществ, которые можно получить из исходного

A
A B
B C
D E

B
C
*/

int main(){
    char basic,basic_after;
    int i;
    Queue* queue=queue_create();
    std::cout << "Input basic substance ";
    std::cin >> basic;
    basic_after=basic;
    char first,second;
    std::cout << "Inpute how many transformations will there be ";
    std::cin >> i;
    while (!i==0){
        std::cin >> first>> second;
        if (first == basic_after){
            queue_insert(queue,second);
            basic_after = second;
        }
        i--;
    }
    std::cout << std::endl;
    while (queue_empty){
        std::cout << (char) queue_get(queue) << std::endl;
        queue_remove(queue);
    }
    queue_delete(queue);
    return 0;
}