#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "queue.h"

struct Point {
    int z;
    int r;
    int c;
};

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: Lab3 <input_file>\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    if (!in.is_open()) {
        std::cerr << "Cannot open input file\n";
        return 1;
    }

    std::vector<std::vector<std::string>> maze;
    std::vector<std::string> currentLayer;
    std::string line;

    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line.empty()) {
            if (!currentLayer.empty()) {
                maze.push_back(currentLayer);
                currentLayer.clear();
            }
        } else {
            currentLayer.push_back(line);
        }
    }
    if (!currentLayer.empty()) {
        maze.push_back(currentLayer);
    }

    if (maze.empty() || maze[0].empty() || maze[0][0].empty()) {
        std::cerr << "Empty maze\n";
        return 1;
    }

    int layers = static_cast<int>(maze.size());
    int rows = static_cast<int>(maze[0].size());
    int cols = static_cast<int>(maze[0][0].size());

    Point start = {-1, -1, -1};
    for (int z = 0; z < layers; ++z) {
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (maze[z][r][c] == 'X') {
                    start = {z, r, c};
                }
            }
        }
    }

    if (start.z == -1) {
        std::cerr << "Start position X not found\n";
        return 1;
    }

    std::vector<std::vector<std::vector<bool>>> visited(
        layers, std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false))
    );

    Queue<Point> q;
    q.insert(start);
    visited[start.z][start.r][start.c] = true;

    char nearestDigit = '\0';

    int dz[] = {0, 0, 0, 0, 1, -1};
    int dr[] = {-1, 1, 0, 0, 0, 0};
    int dc[] = {0, 0, -1, 1, 0, 0};

    while (!q.empty()) {
        Point p = q.get();
        q.remove();

        char cell = maze[p.z][p.r][p.c];
        if (cell >= '0' && cell <= '9') {
            nearestDigit = cell;
            break;
        }

        for (int i = 0; i < 6; ++i) {
            int nz = p.z + dz[i];
            int nr = p.r + dr[i];
            int nc = p.c + dc[i];

            if (nz >= 0 && nz < layers && nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                if (!visited[nz][nr][nc] && maze[nz][nr][nc] != '#') {
                    visited[nz][nr][nc] = true;
                    q.insert({nz, nr, nc});
                }
            }
        }
    }

    if (nearestDigit != '\0') {
        std::cout << nearestDigit << "\n";
    }

    return 0;
}