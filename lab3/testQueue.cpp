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
    std::string str[2];
    bool empty = true;
    std::ifstream in("E:\\text.txt");
    if (in.is_open()) {
        while (!in.eof()) {
            for (int i = 0; i < 2; ++i) {
                std::getline(in, str[i]);
            }
        }
    } else
        std::cout << "Nope";
    for (int i = 0; i < str[0].size(); ++i) {
        _queue.insert(str[0][i]);
    }
    int num = str[1].size();
    int k = num;
    while (empty) {
        int n = k;
        for (int j = 0; j < num; ++j) {
            if (_queue.get() == str[1][j]) {
                k--;
                _queue.remove();
            }
        }
        if (n - k == 0) {
            _queue.remove();
        }
        if (k == 0) {
            empty = false;
            std::cout << "Yes";
        }
        if (_queue.empty() && k != 0) {
            empty = false;
            std::cout << "No";
        }
    }

    return 0;

}




