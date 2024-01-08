#include <iostream>
#include <fstream>
#include "vector.h"
#include "queue.h"


struct Position {
    unsigned long long x=0, y=0, dist=0;
    int check;
};

bool isValid(unsigned long long x, unsigned long long y, Vector<std::string>& maze) {
    if (x < 0 || y < 0 || x >= maze.size() || y >= maze.get(0).size())
        return false;
    if (maze.get(x)[y] == '#')
        return false;
    return true;
}

int findNearestNumber(Position start, Vector<std::string>& maze) {
    Queue<Position> q;
    if (start.check == 0) {
        return -2;
    }
    if (start.check >1) {
        return -3;
    }
    q.insert(start);
    int fullRoundCounter = 0;
    int biggest = 0;
    for (int i = 0; i < maze.size();i++) {
        int size = maze.get(i).size();
        if (size > biggest) {
            biggest = size;
        }
    }

    while (!q.empty()) {
        Position p = q.get();
        q.remove();
        if (isdigit(maze.get(p.x)[p.y]))
            return maze.get(p.x)[p.y] - '0';
        if (p.x == start.x && p.y == start.y) {
            fullRoundCounter++;
            if (fullRoundCounter >= maze.size() * biggest) {
                return -1; 
            }
        }
        Position moves[] = { {0, 1, p.dist + 1}, {0, -1, p.dist + 1}, {1, 0, p.dist + 1}, {-1, 0, p.dist + 1} };
        for (auto move : moves) {
            unsigned long long newX = p.x + move.x;
            unsigned long long newY = p.y + move.y;
            if (isValid(newX, newY, maze)) {
                maze.get(newX)[newY] = '#';
                q.insert({ newX, newY, move.dist });
            }
        }
    }
    return -4;
}

int main() {
    setlocale(0, "Russian");
    std::ifstream file("input.txt");
    Vector<std::string> maze;
    Position start;
    char c;
    int check=0;
    bool isNeed=true;

    while (file.get(c)) {
        std::string row;
        while (c != '\n' && !file.eof()) {
            row.push_back(c);
            if (c == 'X') {
                check++;
                start = { maze.size(), row.size() - 1, 0,check };
            }
            file.get(c);
        }
        maze.push_back(row);
    }
    file.close();

    for (int i = 0; i < maze.size(); i++) {
        		std::cout << "[ ";
        		for (int j = 0; j < maze.get(i).size(); j++) {
        			std::cout << maze.get(i)[j] << " ";
        		}
        		std::cout << "]" << std::endl;
        	}

    int nearestNumber = findNearestNumber(start, maze);
    if (nearestNumber == -1) {
        std::cout << "Пути нет" << std::endl;
    }
    else if (nearestNumber == -2) {
        std::cout << "Нет отправной точки" << std::endl;
    }
    else if (nearestNumber == -3) {
        std::cout << "Более одной отправной точки" << std::endl;
    }
    else if (nearestNumber == -4) {
        std::cout << "Возникла непредвиденная ошибка" << std::endl;
    }
    else {
        std::cout << nearestNumber << std::endl;
    }
    return 0;
}
