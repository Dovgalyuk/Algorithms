#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "queue.h"

struct Point {
    int r, c;
};

int main(int argc, char* argv[]) {
    std::vector<std::string> maze;
    std::string line;
    
    if (argc > 1) {
        std::ifstream fin(argv[1]);
        if (!fin.is_open()) {
            std::cerr << "Не удалось открыть файл: " << argv[1] << std::endl;
            return 1;
        }
        while (std::getline(fin, line)) {
            if (!line.empty()) {
                maze.push_back(line);
            }
        }
    } else {
        while (std::getline(std::cin, line)) {
            if (!line.empty()) {
                maze.push_back(line);
            }
        }
    }

    if (maze.empty()) return 0;

    int rows = maze.size();
    int cols = maze[0].size();
    
    Point start = {-1, -1};

    // стартовая точка X
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (maze[r][c] == 'X') {
                start = {r, c};
                break;
            }
        }
        if (start.r != -1) break;
    }

    if (start.r == -1) {
        std::cerr << "стартовая точка X не найдена!" << std::endl;
        return 1;
    }

    Queue *q = queue_create();
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    auto encode = [cols](int r, int c) { return r * cols + c; };
    auto decode = [cols](int val, int &r, int &c) {
        r = val / cols;
        c = val % cols;
    };

    queue_insert(q, encode(start.r, start.c));
    visited[start.r][start.c] = true;
    
    int reachable_count = 0;

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    while (!queue_empty(q)) {
        int val = queue_get(q);
        queue_remove(q);
        
        int r, c;
        decode(val, r, c);
        reachable_count++;

        if (maze[r][c] != 'X') {
            maze[r][c] = 'x';
        }

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                if (maze[nr][nc] == '.' && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    queue_insert(q, encode(nr, nc));
                }
            }
        }
    }

    queue_delete(q);


    std::cout << reachable_count << "\n";
    for (int r = 0; r < rows; ++r) {
        std::cout << maze[r] << "\n";
    }

    return 0;
}
