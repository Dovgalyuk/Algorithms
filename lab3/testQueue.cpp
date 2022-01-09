//
// Created by Даниил on 01.12.2021.
//
#include <iostream>
#include <fstream>
#include <string>
#include <queue.h>

typedef Queue<char> queue;

int main() {
    queue _queue;
    char str;
    std::ifstream in("E:\\text.txt");

    while (str != '\n') { // Пока не находит enter
        in.get(str); // Берем символ из файла
        _queue.insert(str); // И добавляем его в очередь
    }

    while(in >> str) { //Пока есть символы, которые можно прочитать
        while (!_queue.empty() && str != _queue.get()) { //Пока очередь не пустая и символ не равен строке
            _queue.remove();//Удаляем элемент из очереди
        }
        if(_queue.empty()) { //Если очередь пустая
            std::cout << "No"; //Выводим нет
            return 0;
        }
        _queue.remove(); //Удаляем элемент из очереди
    }
    std::cout << "Yes";//В любом другом случае выводим да
    return 0;

}
