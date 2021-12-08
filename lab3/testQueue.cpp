//
// Created by Даниил on 01.12.2021.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue.h>

typedef Queue<char> queue;

int main() {
    queue _queue;
    char str;
    bool end = true;
    std::vector<char> stroka;
    std::ifstream in("E:\\text.txt");
    for (int i = 0; i < 4; ++i) {
        in >> str;
        _queue.insert(str);
    }

    for (int i = 0; i < 3; ++i) {
        in >> str;
        stroka.push_back(str);
    }

    int k = stroka.size();
    while (end) {
        for (int i = 0; i < stroka.size(); ++i) {
            if (stroka[i] == _queue.get()) {
                _queue.remove();
                stroka.erase(stroka.begin() + i);
                i = stroka.size();
            }
            if (stroka.empty()) {
                end = false;
            }
        }
        if (k == stroka.size()) {
            _queue.remove();
        }
        if (_queue.empty()) {
            end = false;
        }
        k = stroka.size();
    }

    if (stroka.empty())
        std::cout << "Yes";
    else
        std::cout << "No";

    return 0;

}


