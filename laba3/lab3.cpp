#include<iostream>
#include "queue.h"
#include <vector>
#include "fstream"
#include "string"

int main()
{
    auto *elements = new Queue<std::pair<size_t, size_t>>();
    auto *neighbors = new Queue<std::pair<size_t, size_t>>();
    size_t counter = 0;

    std::ifstream file;
    file.open(R"(C:\Users\drs\CLionProjects\Algorithms\laba3\files)");
    std::vector<std::vector<char>> maze;
    std::string buffer;
    while (!file.eof())
    {
        std::getline(file, buffer);
        maze.emplace_back(buffer.begin(), buffer.end());
    }

    for (size_t i = 0; i < maze.size() && counter == 0; ++i) {
        for (size_t j = 0; j < maze[0].size(); ++j) {
            if (maze[i][j] == 'X') {
                elements->insert(std::pair<size_t, size_t>(i,j));
                ++counter;
                break;
            }
        }
    }

    do {
        while (!elements->empty()) {
            std::pair<size_t,size_t> current = elements->get();
            elements->remove();
            if (maze[current.first - 1][current.second] == '.') {
                ++counter;
                maze[current.first - 1][current.second] = 'X';
                neighbors->insert(std::pair<size_t, size_t>(current.first - 1, current.second));
            }
            if (maze[current.first + 1][current.second] == '.') {
                ++counter;
                maze[current.first + 1][current.second] = 'X';
                neighbors->insert(std::pair<size_t, size_t>(current.first + 1, current.second));
            }
            if (maze[current.first][current.second - 1] == '.') {
                ++counter;
                maze[current.first][current.second - 1] = 'X';
                neighbors->insert(std::pair<size_t, size_t>(current.first, current.second - 1));
            }
            if (maze[current.first][current.second + 1] == '.') {
                ++counter;
                maze[current.first][current.second + 1] = 'X';
                neighbors->insert(std::pair<size_t, size_t>(current.first, current.second + 1));
            }
        }

        while (!neighbors->empty()) {
            elements->insert(neighbors->get());
            neighbors->remove();
        }
    } while (!elements->empty());

    std::cout << counter << std::endl;

    for (const auto& line: maze) {
        for (const auto& el: line) {
            std::cout << el;
        }
        std::cout << std::endl;
    }

    file.close();
    return 0;
}

