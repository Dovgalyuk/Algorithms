//
// Created by KirilliriK on 16.09.2021.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../LibraryCPPTemplate/queue.h"

struct Position{
    int x, y;
};

void fillMap();

int main() {
    fillMap();
}

void checkTiles(std::vector<std::string>& map, Queue<Position> &positions, int &freeTilesCount) {
    Position position = positions.get();
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x == 0 && y == 0) continue; // Мне кажется что в учебных целях такой код читабельнее чем 4 if'а
            if (x == 1 && y == 1) continue;
            if (x == -1 && y == -1) continue;
            if (x == 1 && y == -1) continue;
            if (x == -1 && y == 1) continue;

            Position newPosition = position;
            newPosition.x += x;
            newPosition.y += y;
            if (newPosition.x < 0 || newPosition.y < 0 || newPosition.y >= map.size() || newPosition.x >= map.at(newPosition.y).size()) continue;

            char ch = map.at(newPosition.y).at(newPosition.x);

            switch (ch) {
                case '#':
                case 'X':
                    continue;
                case '.':
                    positions.insert(newPosition);
                    map.at(newPosition.y).replace(newPosition.x, 1, "X");
                    freeTilesCount++;
                    continue;
                default:
                    std::cout << "Unknown tile type" << std::endl;
                    exit(-2);
            }
        }
    }
    positions.remove();
}

void findFreeTiles(std::vector<std::string>& map) {
    Queue<Position> positions;
    int freeTilesCount = 1;

    Position startPosition{0, 0};
    for (const std::string &str : map) {
        startPosition.x = str.find_first_of('X');
        if (startPosition.x != std::string::npos) break;
        startPosition.y++;
    }
    positions.insert(startPosition);
    while (!positions.empty()) {
        checkTiles(map, positions, freeTilesCount);
    }
    std::cout << freeTilesCount << std::endl;
    for (const std::string &str : map) {
        std::cout << str << std::endl;
    }
}

void fillMap() {
    std::vector<std::string> map;
    std::ifstream is("../../../Algorithms/Result/input/input.txt");
    std::string inputString;
    if (is.is_open()) {
        while(std::getline(is, inputString)) {
            map.push_back(inputString);
        }
    } else {
        std::cout << "Input file not found" << std::endl;
        exit(-1);
    }
    findFreeTiles(map);
}