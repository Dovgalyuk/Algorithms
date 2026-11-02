#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "queue.h"

int main(int argc, char *argv[])
{
    std::ifstream file;
    std::istream *input = &std::cin;
    if (argc > 1) {
        file.open(argv[1]);
        input = &file;
    }

    std::vector<std::string> maze;
    std::string line;
    while (std::getline(*input, line))
        if (!line.empty()) maze.push_back(line);

    if (maze.empty()) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    int rows = maze.size(), columns = maze[0].size();
    int start = -1, finish = -1;
    for (int r = 0; r < rows; r++) {
        if (maze[r].size() != static_cast<size_t>(columns)) {
            std::cout << "IMPOSSIBLE\n";
            return 0;
        }
        for (int c = 0; c < columns; c++) {
            if (maze[r][c] == 'X') start = r * columns + c;
            if (maze[r][c] == 'Y') finish = r * columns + c;
        }
    }
    if (start == -1 || finish == -1) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    std::vector<int> parent(rows * columns, -2);
    Queue queue;
    parent[start] = -1;
    queue.insert(start);
    int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};
    while (!queue.empty() && parent[finish] == -2) {
        int current = queue.get();
        queue.remove();
        int r = current / columns, c = current % columns;
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= columns || maze[nr][nc] == '#') continue;
            int next = nr * columns + nc;
            if (parent[next] != -2) continue;
            parent[next] = current;
            queue.insert(next);
        }
    }

    if (parent[finish] == -2) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (int cell = finish; cell != start; cell = parent[cell]) {
        int r = cell / columns, c = cell % columns;
        if (maze[r][c] != 'Y') maze[r][c] = 'x';
    }
    for (const std::string &row : maze) std::cout << row << '\n';
}
