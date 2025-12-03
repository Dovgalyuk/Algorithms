#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"

struct Point {
    int x, y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}};

const int INF = 1000000000;
const int MAX_SIZE = 100; 

void task(std::istream& in) {
    std::string maze[MAX_SIZE];
    std::string line;
    Point start = { -1, -1 };
    int H = 0;
    while (std::getline(in, line) && H < MAX_SIZE) {
        if (!line.empty()) {
            maze[H] = line;
            H++;
        }
    }

    int W = static_cast<int>(maze[0].size());

    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            if (maze[y][x] == 'X') {
                start.x = x;
                start.y = y;
                break;
            }
        }
        if (start.x != -1) break;
    }
    int dist[MAX_SIZE][MAX_SIZE];
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            dist[y][x] = INF;
        }
    }

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
            if (dist[ny][nx] == INF) {
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