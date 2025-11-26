#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "queue.h"

struct Point { int x, y; };

void task(std::istream& in) {
    std::vector<std::string> maze;
    std::string line;
    Point start = { -1, -1 };
    while (std::getline(in, line)) {
        if (!line.empty()) maze.push_back(line);
    }
    int H = static_cast<int>(maze.size());
    int W = static_cast<int>(maze[0].size());
    for (int y = 0; y < H; ++y)
        for (int x = 0; x < W; ++x)
            if (maze[y][x] == 'X') start = { x, y };

    std::vector<std::vector<int>> dist(H, std::vector<int>(W, INT_MAX));
    Queue* q = queue_create();
    queue_insert(q, start.y * W + start.x);
    dist[start.y][start.x] = 0;

    const int dx[4] = { -1, 1, 0, 0 };
    const int dy[4] = { 0, 0, -1, 1 };
    int ans = -1;

    while (!queue_empty(q)) {
        int v = queue_get(q);
        queue_remove(q);
        int y = v / W, x = v % W;
        if (isdigit(maze[y][x])) {
            ans = maze[y][x] - '0';
            break;
        }
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= W || ny < 0 || ny >= H) continue;
            if (maze[ny][nx] == '#') continue;
            if (dist[ny][nx] == INT_MAX) {
                dist[ny][nx] = dist[y][x] + 1;
                queue_insert(q, ny * W + nx);
            }
        }
    }
    queue_delete(q);
    std::cout << ans << std::endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }
    std::ifstream file(argv[1]);
    task(file);
    file.close();
}
