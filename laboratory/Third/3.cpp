#include <iostream>
#include "queue.h"

/*
Задано начальное вещество и список химических реакций,
в которых оно превращается в другое вещество.
Написать программу, использующую поиск в ширину,
и выводящую список веществ, которые можно получить из исходного

A
A->B
B->C
D->E
Ответ: B C

A
A->B
B->C
C->E
C->F
Ответ: B C E F

A
G->H
G->K
I->J
A->C
B->D
C->F
A->B
C->E
Ответ: B C D E F

A
A->B
B->A
B->C
*/

void inputSTR(int i,std::string &str){
    std::string str_input;
    while(i!=0){
        std::cin >> str_input;
        str.push_back(str_input[0]);
        str.push_back(str_input[3]);
        str.push_back(' ');
        str_input.clear();
        i--;
    }       
}

int main(){
    char basic;
    std::cout << "Input basic substance ";
    std::cin >> basic;
    
    Queue* queue=queue_create();
    queue_insert(queue,basic);
    
    int i,point;
    std::cout << "Inpute how many transformations will there be ";
    std::cin >> i;
    
    std::string str,str_save;
    inputSTR(i,str);

    while (!queue_empty(queue)){
        for(int j = 0;j < str.length(); j+=3)
        {
            if ((char)queue_get(queue) == str[j])
            {
                point = 0;
                if (!str_save.empty())
                {
                    for (auto i=0;i<str_save.length();i++)
                    {
                        if ((str[j+1]==str_save[i]) || (str[j+1]==basic))
                        {
                            point = 1;
                        }
                    }
                }
                if (point == 1){
                    continue;
                }
                str_save.push_back(str[j+1]);
                queue_insert(queue,str[j+1]);
            }
        }
        queue_remove(queue);
    }
    std::cout << str_save;
    queue_delete(queue);
    return 0;
}