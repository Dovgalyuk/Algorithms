#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "queue.h"

typedef std::vector<std::string> Maze;

char findDigit(Maze maze) {
    
    if (maze.empty()) return 0;

    int n = (int)maze.size();
    int m = (int)maze[0].size();

    Queue<int> q;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (maze[i][j] == 'X') {
                q.insert(i * m + j);
                maze[i][j] = '#';
            }

    int dx[4] = { -1, 1, 0, 0 };
    int dy[4] = { 0, 0, -1, 1 };

    while (!q.empty())
    {
        int v = q.get();
        q.remove();

        int x = v / m;
        int y = v % m;

        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

            char c = maze[nx][ny];
            if (c == '#') continue;

            if (c >= '0' && c <= '9')
                return c;

            maze[nx][ny] = '#';
            q.insert(nx * m + ny);
        }
    }

    return 0;
}


int main(int argc, char** argv) {
    if (argc < 2) return 1;

    std::ifstream in(argv[1]);
    if (!in) return 1;

    Maze maze;
    std::string line;

    while (std::getline(in, line))
        maze.push_back(line);

    char ans = findDigit(maze);
    if (ans) std::cout << ans << std::endl;

    return 0;
}