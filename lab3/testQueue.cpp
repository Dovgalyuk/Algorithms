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
    int count = -1;
    char str;
    std::ifstream in("E\\text.txt");

    while (str != '\n') {
        in.get(str);
        _queue.insert(str);
    }

    while (!_queue.empty())
    {
        if (in.eof()) {
            in >> str;
            count++;
        }
        if (_queue.get() == str)
        {
            _queue.remove();
            count--;
        } else
            _queue.remove();
    }

    if (count == 0)
        std::cout << "Yes";
    else
        std::cout << "No";
    return 0;


}

