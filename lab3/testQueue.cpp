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
    std::string stroka;
    std::ifstream in("E:\\text.txt");

    while (str != '\n') {
        in.get(str);
        _queue.insert(str);
    }

    while(in) {
        in >> str;
        if(stroka[stroka.size() - 1] == str && in.eof())
            break;
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


