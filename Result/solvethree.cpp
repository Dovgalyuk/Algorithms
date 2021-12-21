#include <iostream>
#include <vector>
#include <fstream>
#include "queue.h"

struct Position {
    int x, y;
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

        const Tile checkTile = map[position.y][position.x];
        for (size_t i = 0; i < 4; i++) {
            const int x = position.x + dx[i];
            const int y = position.y + dy[i];
            if (x < 0 || y < 0 || y >= map.size() || x >= map[y].size()) continue;

            const Tile tile = map[y][x];
            if (tile.ch == 'X') {
                find = true;
                break;
            }

            if (checkTile.weight - tile.weight != 1) continue;

            position.x = x;
            position.y = y;
            map[position.y][position.x].ch = 'x';
            break;
        }
        if (find) break;
    }
}

bool checkTiles(TileMap& map, PositionsQueue &positions) {
    const Position checkPosition = positions.get();
    const Tile checkTile = map[checkPosition.y][checkPosition.x];

    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

    for (size_t i = 0; i < 4; i++) {
        const int x = dx[i] + checkPosition.x;
        const int y = dy[i] + checkPosition.y;

        Position newPosition = checkPosition;
        newPosition.x = x;
        newPosition.y = y;
        if (x < 0 || y < 0 || y >= map.size() || x >= map[y].size()) continue;

        const char ch = map.at(y).at(x).ch;

        switch (ch) {
            case '#':
            case 'X':
                continue;
            case '.':
                if (map[y][x].weight != 0 && map[y][x].weight <= checkTile.weight) continue;

                positions.insert(newPosition);
                map[y][x].weight = checkTile.weight + 1;
                continue;
            case 'Y':
                map[y][x].weight = checkTile.weight + 1;
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

    Position startPosition{0, 0};

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
    std::ifstream is("../../../Algorithms/Result/input/input.txt");
    std::string inputString;
    if (is.is_open()) {
        while(std::getline(is, inputString)) {
            std::vector<Tile> vector;

            for (char ch : inputString) {
                vector.emplace_back(ch, 0);
            }
            map.push_back(vector);
        }
    } else {
        std::cout << "Input file not found" << std::endl;
        exit(-1);
    }
    findPath(map);
}