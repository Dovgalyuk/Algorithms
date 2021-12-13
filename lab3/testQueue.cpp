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
    int count = 0;
    char str;
    bool end = true;
    std::string stroka;
    std::ifstream in("E:\\text.txt");

    for (int i = 0; i < 3; ++i) {
        in >> str;
        _queue.insert(str);
    }

    for (int i = 0; i < 3; ++i) {
        in >> str;
        stroka.push_back(str);
    }

    while(!_queue.empty()) {
        for (int i = 0; i < stroka.size(); ++i) {
            if (_queue.get() == stroka[i]) {
                count++;
                i = stroka.size();
            }
        }
        _queue.remove();
    }

    if(count == stroka.size()) {
        std::cout << "Yes";
    }
    else
        std::cout << "No";
    return 0;


}


