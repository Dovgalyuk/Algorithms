#include <iostream>
#include <vector>
#include <fstream>
#include "queue.h"

struct Position{
    int x, y;
    int weight;
};

struct Tile {
    char ch;
    int weight;

    Tile() {
        ch = '@';
        weight = -1;
    }

    Tile(char ch, int weight) {
        this->ch = ch;
        this->weight = weight;
    }
};

typedef Queue<Position> PositionsQueue;
typedef std::vector<std::vector<Tile>> TileMap;

void fillMap();

int main() {
    fillMap();
    return 0;
}

void findReturnPath(TileMap& map, Position position) {
    bool find = false;
    for(;;) {
        const int dx[] = {-1, 1, 0, 0};
        const int dy[] = {0, 0, -1, 1};
        for (size_t i = 0; i < 4; i++) {
            int x = position.x + dx[i];
            int y = position.y + dy[i];
            if (x < 0 || y < 0 || y>= map.size() || x >= map[y].size()) continue;

            auto tile = map[y][x];
            if (tile.ch == 'X') {
                find = true;
                break;
            }
            if (position.weight - tile.weight != 1) continue;
            position.x = x;
            position.y = y;
            position.weight = tile.weight;
            map[position.y][position.x].ch = 'x';
            break;
        }
        if (find) break;
    }
}

bool checkTiles(TileMap& map, PositionsQueue &positions) {
    Position checkPosition = positions.get();
    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};
    for (size_t i = 0; i < 4; i++) {
        int x = dx[i];
        int y = dy[i];
        Position newPosition = checkPosition;
        newPosition.x += x;
        newPosition.y += y;
        newPosition.weight = checkPosition.weight + 1;
        if (newPosition.x < 0 || newPosition.y < 0 || newPosition.y >= map.size() || newPosition.x >= map[newPosition.y].size()) continue;

        char ch = map.at(newPosition.y).at(newPosition.x).ch;

        switch (ch) {
            case '@':
            case '#':
            case 'X':
                continue;
            case '.':
                positions.insert(newPosition);
                map[newPosition.y][newPosition.x].ch = '@';
                map[newPosition.y][newPosition.x].weight = newPosition.weight;
                continue;
            case 'Y':
                findReturnPath(map, newPosition);
                return true;
            default:
                std::cout << "Unknown tile type " << ch << std::endl;
                exit(-2);
        }
    }
    positions.remove();
    return false;
}

void findPath(TileMap& map) {
    PositionsQueue positions;

    Position startPosition{0, 0, 1};
    bool find = false;
    for (auto &vector : map) {
        startPosition.x = 0;
        for (auto &tile : vector) {
            if (tile.ch == 'X') {
                find = true;
                break;
            }
            startPosition.x++;
        }
        if (find) break;
        startPosition.y++;
    }
    positions.insert(startPosition);
    find = false;
    while (!positions.empty()) {
        if (checkTiles(map, positions)) {
            find = true;
            break;
        }
    }

    if (!find) {
        std::cout << "IMPOSSIBLE" << std::endl;
        return;
    }
    for (auto &vector : map) {
        for (auto &tile: vector) {
            std::cout << tile.ch;
        }
        std::cout << std::endl;
    }
}

void fillMap() {
    TileMap map;
    std::ifstream is("../../../Algorithms/Result/input.txt");
    std::string inputString;
    if (is.is_open()) {
        int i = 0;
        while(std::getline(is, inputString)) {
            std::vector<Tile> vector;
            for (char ch : inputString) {
                vector.emplace_back(ch, 0);
            }
            map.push_back(vector);
            i++;
        }
    } else {
        std::cout << "Input file not found" << std::endl;
        exit(-1);
    }
    findPath(map);
}