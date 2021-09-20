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

typedef Queue<Position> PositionsQueue;
typedef std::vector<std::string> TileMap;

void fillMap();

int main() {
    fillMap();
}

void checkTiles(TileMap& map, PositionsQueue &positions, int &freeTilesCount) {
    Position checkPosition = positions.get();
    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};
    for (size_t i = 0; i < 4; i++) {
        int x = dx[i];
        int y = dy[i];
        Position newPosition = checkPosition;
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
                map[newPosition.y][newPosition.x] = 'X';
                freeTilesCount++;
                continue;
            default:
                std::cout << "Unknown tile type" << std::endl;
                exit(-2);
        }
    }
    positions.remove();
}

void findFreeTiles(TileMap& map) {
    PositionsQueue positions;
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
    TileMap map;
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